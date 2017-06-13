#include <sys/socket.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "server/proceed.h"
#include "server.h"

static bool gl_stop = false;

static void set_quit(int sig)
{
  (void)sig;
  gl_stop = true;
}

static int		set_fds(t_server *server,
                                  fd_set *fds_read,
                                  fd_set *fds_write)
{
  t_client              *client;
  int                   ia;
  int			max;

  ia = 0;
  FD_ZERO(fds_read);
  FD_ZERO(fds_write);
  max = set_gui(server, fds_read, fds_write);
  FD_SET(server->ia_sock, fds_read);
  max = server->ia_sock > max ? server->ia_sock : max;
  while (ia < server->config.max_player * 2)
  {
    client = &server->game.clients[ia];
    if (client->alive)
    {
      FD_SET(client->sock, fds_read);
      if (find_command(&client->w))
        FD_SET(client->sock, fds_write);
      max = client->sock > max ? client->sock : max;
    }
    ++ia;
  }
  return (max + 1);
}

static int running(t_server *server)
{
  fd_set reads;
  fd_set writes;
  Socket max;

  while (!gl_stop)
  {
    max = set_fds(server, &reads, &writes);
    printf("Waiting on Select...\n");
    if (select(max, &reads, &writes, NULL, NULL) < 0)
    {
      perror("Select error");
      free(server->game.clients);
      return (1);
    }
    else if (proceed(server, &reads, &writes))
    {
      free(server->game.clients);
      return (1);
    }
  }
  free(server->game.clients);
  //TODO verify player disconnection
  return (0);
}

static int init_server(t_server *server)
{
  t_config *config = &server->config;

  server->game.width = config->width;
  server->game.height = config->height;
  return ((server->game.map = malloc(
      sizeof(*server->game.map) *
      config->height * config->width)) == NULL ||
      (server->game.clients = calloc(config->max_player * 2,
          sizeof(*server->game.clients))) == NULL);
}

int launch_server(t_server *server)
{
  struct sigaction action;

  memset(&action, 0, sizeof(action));
  action.sa_flags = SA_SIGINFO;
  action.sa_handler = &set_quit;
  return (sigaction(SIGINT, &action, NULL) == -1 ||
          signal(SIGPIPE, SIG_IGN) == SIG_ERR ||
          init_server(server) ||
          create_socket(&server->ia_sock, server->config.port,
                        server->config.max_player * 2) ||
          create_socket(&server->gui_sock, 8484, 1) ||
          running(server));
}
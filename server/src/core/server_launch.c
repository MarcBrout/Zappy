/*
** server_launch.c for zappy in server/src/core
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sun Jun 25 02:51:50 2017 brout_m
** Last update Tue Jun 27 17:12:13 2017 brout_m
*/

#include <sys/socket.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "server/gui_events.h"

static bool		gl_stop = false;

void	set_quit(int sig)
{
  (void)sig;
  gl_stop = true;
}

static int		set_fds(t_server *server,
				fd_set *fds_read,
				fd_set *fds_write)
{
  t_client		*client;
  int			ia = 0;
  int			max;

  FD_ZERO(fds_read);
  FD_ZERO(fds_write);
  max = set_gui(server, fds_read, fds_write);
  FD_SET(server->ia_sock, fds_read);
  max = server->ia_sock > max ? server->ia_sock : max;
  while (ia < server->game.max_slot)
    {
      client = &server->game.clients[ia];
      if (client->active)
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

static int		running(t_server *server)
{
  struct timeval	time;
  fd_set		reads;
  fd_set		writes;
  Socket		max;
  bool			end = false;

  while (!end)
    {
      if (gl_stop)
	{
	  event_seg(server, server->config.teams[check_winner(server)].name);
	  end = true;
	}
      time.tv_sec = 0;
      time.tv_usec = 10;
      max = set_fds(server, &reads, &writes);
      if (select(max, &reads, &writes, NULL, &time) < 0)
	{
	  perror("Select error");
	  return (1);
	}
      else if (proceed(server, &reads, &writes))
	return (1);
    }
  return (0);
}

static int		init_server(t_server *server)
{
  t_config		*config = &server->config;

  server->game.width = config->width;
  server->game.height = config->height;
  log_this("Setting up Server...\n");
  if ((server->game.map = calloc(config->height * config->width,
				 sizeof(*server->game.map))) == NULL)
    return (1);
  log_this("Allocated map:\n\tx: %d\n\ty: %d\n",
	   config->width, config->height);
  if ((server->game.clients = calloc(config->max_player * config->team_count,
				     sizeof(*server->game.clients))) == NULL)
    return (1);
  log_this("Allocated clients:\n\tcount: %d\n\tsize: %d\n",
	   config->max_player * config->team_count,
	   sizeof(*server->game.clients));
  server->game.max_slot = config->max_player * config->team_count;
  generate_ressources_start(server);
  srand(time(NULL));
  set_teams(&server->config);
  return (0);
}

int			launch_server(t_server *server)
{
  struct sigaction	action;

  memset(&action, 0, sizeof(action));
  action.sa_flags = SA_SIGINFO;
  action.sa_handler = &set_quit;
  log_this("Launching Server...\n");
  init_timer(server->config.time);
  if (sigaction(SIGINT, &action, NULL) == -1 ||
      signal(SIGPIPE, SIG_IGN) == SIG_ERR ||
      init_server(server) ||
      create_socket(&server->ia_sock, server->config.port, 1000))
    return (1);
  log_this("Running Server...\n");
  if (running(server))
    {
      free_resources(server);
      return (1);
    }
  free_resources(server);
  return (0);
}

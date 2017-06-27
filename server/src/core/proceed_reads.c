/*
** proceed_reads.c for zappy in server/src/core
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sun Jun 25 02:43:34 2017 brout_m
** Last update Tue Jun 27 17:07:12 2017 brout_m
*/
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <server/gui_events.h>
#include "server.h"

int			find_ID(t_server *server, ID client, bool active)
{
  ID			cli;

  cli = 0;
  while (cli < server->game.max_slot)
    {
      if (!active && !server->game.clients[cli].alive)
	return (cli);
      if (active && client == server->game.clients[cli].id)
	return (cli);
      ++cli;
    }
  return (-1);
}

static char const	ctrl_c[5] = {0xff, 0xf4, 0xff, 0xfd, 0x06};

static int		read_client(t_server *server,
				    t_client *client,
				    Socket sock)
{
  char			buff[MESSAGE_MAX_SIZE];
  ssize_t		len;

  log_this("Received command from CLIENT : %d\n", client->id);
  memset(buff, 0, MESSAGE_MAX_SIZE);
  if ((len = read(sock, buff, MESSAGE_MAX_SIZE - 1)) < 0)
    {
      perror("Read from client error");
      return (1);
    }
  if (!len || strchr(buff, 4) ||
      (len == sizeof(ctrl_c) && !memcmp(buff, ctrl_c, sizeof(ctrl_c))))
    {
      event_pdi(server, client->id);
      close(sock);
      memset(client, 0, sizeof(t_client));
      return (0);
    }
  if (strcmp(buff, "\n"))
    strncircular(&client->r, buff, len);
  return (0);
}

static int		read_gui(t_client *gui, Socket sock)
{
  char			buff[MESSAGE_MAX_SIZE];
  ssize_t		len;

  log_this("Received command from GUI\n");
  memset(buff, 0, MESSAGE_MAX_SIZE);
  if ((len = read(sock, buff, MESSAGE_MAX_SIZE - 1)) < 0)
    {
      perror("Read from client error");
      return (1);
    }
  if (!len || strchr(buff, 4) ||
      (len == sizeof(ctrl_c) && !memcmp(buff, ctrl_c, sizeof(ctrl_c))))
    {
      close(sock);
      memset(gui, 0, sizeof(t_client));
      return (0);
    }
  if (strcmp(buff, "\n"))
    strncircular(&gui->r, buff, len);
  return (0);
}

int			proceed_reads(t_server *server, fd_set *fds_read)
{
  Socket		sock;

  sock = 0;
  while (sock < server->game.max_slot)
    {
      if (FD_ISSET(sock, fds_read))
	{
	  if ((sock == server->gui_sock && accept_new_gui(server)) ||
	      (sock == server->ia_sock && accept_new_client(server)) ||
	      (sock == server->gui.sock && read_gui(&server->gui, sock)) ||
	      (sock != server->ia_sock && sock != server->gui_sock && sock !=
	       server->gui.sock &&
	       read_client(server,
			   &server->game.clients[find_Socket(server, sock)],
			   sock)))
	    return (1);
	}
      ++sock;
    }
  return (0);
}

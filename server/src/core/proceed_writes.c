/*
** proceed_writes.c for zappy in server/src/core
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sun Jun 25 02:55:25 2017 brout_m
** Last update Sun Jul  2 19:19:18 2017 Edouard
*/
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "server.h"

int			find_Socket(t_server *server, Socket sock)
{
  ID			cli;

  cli = 0;
  while (cli < server->game.max_slot)
    {
      if (server->game.clients[cli].sock == sock)
	return (cli);
      ++cli;
    }
  return (-1);
}

static int		write_out(t_server *server,
                                  t_client *client,
				  char out[MESSAGE_MAX_SIZE],
				  bool cond)
{
  size_t		len;
  ssize_t		written;
  ssize_t		notwritten;

  len = strlen(out);
  if (cond)
    out[len] = '\n';
  if ((written = write(client->sock, out, strlen(out))) < 0)
    {
      perror("Write to client error");
      --server->config.teams[client->ia.team].memberCount;
      close(client->sock);
      memset(client, 0, sizeof(t_client));
      return (0);
    }
  notwritten = strlen(out) - written;
  if (notwritten > 0)
    {
      client->w.remains = true;
      client->w.pos -= notwritten > client->w.pos
	? BUFFER_MAX_SIZE - (notwritten - client->w.pos)
	: client->w.pos - notwritten;
      client->w.len += notwritten;
    }
  return (0);
}

static int		send_client(t_server *server, t_client *client)
{
  size_t		len;
  char			out[MESSAGE_MAX_SIZE];

  memset(out, 0, MESSAGE_MAX_SIZE);
  while (strfromcircular(&client->w, out) || (strlen(out)) ||
	 client->w.remains)
    {
      len = strlen(out);
      if (write_out(server, client, out, len))
	return (1);
      memset(out, 0, MESSAGE_MAX_SIZE);
    }
  return (write_out(server, client, out, strlen(out) > 0));
}

int			write_client(t_server *server, t_client *client, Socket sock)
{
  while (find_command(&client->w))
    {
      if (send_client(server, client))
	return (1);
    }
  if (client->died)
    {
      memset(client, 0, sizeof(*client));
      close(sock);
      return (0);
    }
  return (0);
}

int			proceed_writes(t_server *server, fd_set *fds_write)
{
  ID			id;
  Socket		sock;
  int			pos;

  id = 0;
  while (id < server->game.max_slot)
    {
      if (server->game.clients[id].active)
	{
	  sock = server->game.clients[id].sock;
	  if (FD_ISSET(sock, fds_write))
	    {
	      log_this("Sending commands to CLIENT : %d\n", sock);
	      pos = find_Socket(server, sock);
	      if (write_client(server, &server->game.clients[pos], sock))
		return (1);
	    }
	}
      ++id;
    }
  return (0);
}

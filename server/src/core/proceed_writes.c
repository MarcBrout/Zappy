/*
** proceed_writes.c for zappy in server/src/core
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sun Jun 25 02:55:25 2017 brout_m
** Last update Sun Jun 25 02:55:39 2017 brout_m
*/
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "server.h"

int			find_Socket(t_server *server, Socket sock)
{
  Socket		cli;

  cli = 0;
  while (cli < server->game.max_slot)
    {
      if (server->game.clients[cli].sock == sock)
	return (cli);
      ++cli;
    }
  return (-1);
}

static int		write_out(t_client *client, Socket sock,
				  char out[MESSAGE_MAX_SIZE], bool cond)
{
  size_t		len;
  ssize_t		written;
  ssize_t		notwritten;

  len = strlen(out);
  if (cond)
    out[len] = '\n';
  if ((written = write(sock, out, len + 1)) < 0)
    {
      perror("Write to client error");
      return (1);
    }
  notwritten = (len + 1) - written;
  if (notwritten > 0)
    {
      client->w.remains = true;
      client->w.pos -= notwritten > client->w.pos ?
	BUFFER_MAX_SIZE - (notwritten - client->w.pos) :
	client->w.pos - notwritten;
      client->w.len += notwritten;
    }
  return (0);
}

/*
** If we need to send multiple commands to a client, we must modify
** this function loop to not stop when reading certain commands:
** use strncmp to check whether to stop or not
**/
static int		send_client(t_client *client, Socket sock)
{
  size_t		len;
  char			out[MESSAGE_MAX_SIZE];

  memset(out, 0, MESSAGE_MAX_SIZE);
  while (strfromcircular(&client->w, out) ||
	 (strlen(out)) || client->w.remains)
    {
      len = strlen(out);
      if (write_out(client, sock, out, len))
	return (1);
      memset(out, 0, MESSAGE_MAX_SIZE);
    }
  return (write_out(client, sock, out, strlen(out) > 0));
}

static int		write_client(t_client *client, Socket sock)
{
  while (find_command(&client->w))
    {
      if (send_client(client, sock))
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
  Socket		sock;
  int			pos;

  sock = 0;
  while (sock < server->game.max_slot)
    {
      if (FD_ISSET(sock, fds_write))
      {
	if (sock == server->gui.sock)
	  {
	    log_this("Sending commands to GUI\n");
	    if (write_client(&server->gui, sock))
	      return (1);
	  }
	else
	  {
	    log_this("Sending commands to CLIENT : %d\n", sock);
	    pos = find_Socket(server, sock);
	    if (write_client(&server->game.clients[pos], sock))
	      return (1);
	  }
      }
      ++sock;
    }
  return (0);
}

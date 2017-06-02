#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "server.h"

int                  find_Socket(t_server *server, Socket sock)
{
  Socket                cli;

  cli = 0;
  while (cli < server->config.max_player * 2)
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
  ssize_t written;
  ssize_t notwritten;

  len = strlen(out);
  if (cond)
      out[len] = '\n';
  if ((written = write(sock, out, len + 1)) < 0)
    {
      perror("Write to client error");
      return (1);
    }
  notwritten = (len + 1) - written;
  if (notwritten)
  {
    client->w.pos -= notwritten > client->w.pos ?
                     BUFFER_MAX_SIZE - (notwritten - client->w.pos) :
                     client->w.pos - notwritten;
    client->w.len += notwritten;
  }
  return (0);
}

static int		send_client(t_client *client, Socket sock)
{
  size_t		len;
  char			out[MESSAGE_MAX_SIZE];

  memset(out, 0, MESSAGE_MAX_SIZE);
  while (strfromcircular(&client->w, out) ||
         (strlen(out) && !strncmp("322", out, 3))) // TODO CHECK THIS
    {
      len = strlen(out);
      if (write_out(client, sock, out, len && !strncmp("322", out, 3))) //TODO CHECK THIS
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
      if (!client->alive)
	{
	  memset(client, 0, sizeof(*client));
	  close(sock);
	}
    }
  return (0);
}

int			proceed_writes(t_server *server, fd_set *fds_write)
{
  Socket		sock;

  sock = 0;
  while (sock < server->config.max_player * 2)
    {
      if (FD_ISSET(sock, fds_write) &&
	  write_client(&server->game.clients[sock], sock))
	return (1);
      ++sock;
    }
  return (0);
}

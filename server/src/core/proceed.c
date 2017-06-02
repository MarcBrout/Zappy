#include <unistd.h>
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <arpa/inet.h>
#include "server.h"
#include "server/proceed.h"

int                     find_ID(t_server *server, ID client, bool active)
{
  ID                    cli;

  cli = 0;
  while (cli < server->config.max_player * 2)
  {
    if (!active && !server->game.clients[cli].alive)
      return (cli);
    if (active && client == server->game.clients[cli].id)
      return (cli);
    ++cli;
  }
  return (-1);
}

static int		accept_new_client(t_server *server)
{
  static ID             id = 0;
  struct sockaddr_in	addr;
  socklen_t		len;
  int			sock;
  int                   cli;

  len = sizeof(addr);
  if ((sock = accept(server->sock, (struct sockaddr *)&addr, &len)) < 0 ||
      getsockname(sock, (struct sockaddr *)&addr, &len) < 0)
  {
    perror("Client accept error");
    return (1);
  }
  cli = find_ID(server, 0, false);
  server->game.clients[cli].alive = true;
  server->game.clients[cli].sock = sock;
  server->game.clients[cli].id = id;
  ++id;
  return (0);
}

static int		read_client(t_client *client, Socket sock)
{
  static char const	ctrl_c[5] = {0xff, 0xf4, 0xff, 0xfd, 0x06};
  char			buff[MESSAGE_MAX_SIZE];
  ssize_t		len;

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
      memset(client, 0, sizeof(t_client));
      return (0);
    }
  if (strcmp(buff, "\n"))
    strncircular(&client->r, buff, len);
  return (0);
}

static int		proceed_reads(t_server *server, fd_set *fds_read)
{
  Socket		sock;

  sock = 0;
  while (sock < server->config.max_player * 2)
    {
      if (FD_ISSET(sock, fds_read))
	{
	  if ((sock == server->sock && accept_new_client(server)) ||
	      (sock != server->sock &&
	       read_client(&server->game.clients[find_Socket(server, sock)],
                           sock)))
	    return (1);
	}
      ++sock;
    }
  return (0);
}

int			proceed(t_server *server,
				fd_set *fds_read, fd_set *fds_write)
{
  return (proceed_reads(server, fds_read) ||
	//  proceed_commands(server) ||
	  proceed_writes(server, fds_write));
}

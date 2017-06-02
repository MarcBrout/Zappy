#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include "server.h"

static int		bind_and_listen(t_server *server, uint16_t port)
{
  struct sockaddr_in	addr;

  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = INADDR_ANY;
  if (bind(server->sock, (struct sockaddr const *)&addr,
           sizeof(addr)) < 0 || listen(server->sock, 512) < 0)
  {
    perror("Server bind error");
    return (1);
  }
  return (0);
}

int			create_server_socket(t_server *server, uint16_t port)
{
  Socket		sock;
  int			ok;
  struct protoent	*pe;

  ok = 1;
  if (!(pe = getprotobyname("TCP")) ||
      (sock = socket(PF_INET, SOCK_STREAM, pe->p_proto)) < 0 ||
      setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &ok, sizeof(int)) < 0)
  {
    perror("Socket creation error");
    return (1);
  }
  server->sock = sock;
  return (bind_and_listen(server, port));
}
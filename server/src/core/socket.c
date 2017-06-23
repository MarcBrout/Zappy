#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include "server.h"

static int		bind_and_listen(Socket sock, uint16_t port, int q)
{
  struct sockaddr_in	addr;

  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = INADDR_ANY;
  if (bind(sock, (struct sockaddr const *)&addr,
           sizeof(addr)) < 0 || listen(sock, q) < 0)
  {
    perror("Server bind error");
    return (1);
  }

  log_this("Socket %d binded and listened on port : %d\n", sock, port);
  return (0);
}

int			create_socket(Socket *s, uint16_t port, int q)
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
  *s = sock;
  log_this("Created socket : %d\n", sock);
  return (bind_and_listen(sock, port, q));
}
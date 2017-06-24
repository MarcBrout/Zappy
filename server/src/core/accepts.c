//
// Created by brout_m on 09/06/17.
//

#include <netinet/in.h>
#include <stdio.h>
#include "server.h"

int accept_new_gui(t_server *server)
{
  struct sockaddr_in	addr;
  socklen_t		len;
  int			sock;

  len = sizeof(addr);
  if ((sock = accept(server->gui_sock, (struct sockaddr *)&addr, &len)) < 0)
  {
    perror("GUI accept error");
    return (1);
  }
  log_this("Accepted gui on sock : %d\n", sock);
  server->gui.sock = sock;
  server->gui.alive = true;
  return (0);
}

int		accept_new_client(t_server *server)
{
  struct sockaddr_in	addr;
  socklen_t		len;
  int			sock;
  int                   cli;

  len = sizeof(addr);
  if ((sock = accept(server->ia_sock, (struct sockaddr *)&addr, &len)) < 0)
  {
    perror("Client accept error");
    return (1);
  }
  cli = find_ID(server, 0, false);
  server->game.clients[cli].alive = true;
  server->game.clients[cli].sock = sock;
  server->game.clients[cli].id = cli;
  log_this("Accepted client ID: %d on sock : %d\n", cli, sock);
  return (0);
}
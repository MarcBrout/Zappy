/*
** accepts.c for zappy in server/src/core
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sun Jun 25 02:35:22 2017 brout_m
** Last update Tue Jun 27 17:01:04 2017 brout_m
*/
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include "server/gui_commands.h"
#include "server.h"

int			accept_new_gui(t_server *server)
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
  return (send_to_gui(server, "WELCOME\n"));
}

static int		add_slot(t_server *server, int *cli)
{
  uint32_t		size;

  size = sizeof(t_client) * (server->game.max_slot + 1);
  if ((server->game.clients = realloc(server->game.clients, size)) == NULL)
    return (1);
  *cli = server->game.max_slot++;
  return (0);
}

int			accept_new_client(t_server *server)
{
  struct sockaddr_in	addr;
  socklen_t		len;
  int			sock;
  int			cli;

  len = sizeof(addr);
  if ((sock = accept(server->ia_sock, (struct sockaddr *)&addr, &len)) < 0)
    {
      perror("Client accept error");
      return (1);
    }
  cli = find_ID(server, 0, false);
  if (cli < 0 && add_slot(server, &cli))
    return (1);
  server->game.clients[cli].alive = true;
  server->game.clients[cli].sock = sock;
  server->game.clients[cli].id = cli;
  log_this("Accepted client ID: %d on sock : %d\n", cli, sock);
  return (send_to_ia(server, cli, "WELCOME\n"));
}

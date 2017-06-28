/*
** logic_connect_nbr.c for zappy in server
**
** Made by Edouard
** Login   <edouard@epitech.net>
**
** Started on  Tue Jun 27 17:29:36 2017 Edouard
** Last update Tue Jun 27 17:29:42 2017 Edouard
*/

#include "server.h"

int	logic_connect_nbr(t_server *server, ID id, char *cmd)
{
  int	nb_slot;

  (void)cmd;
  nb_slot = count_empty_slot(server, server->game.clients[id].ia.team);
  return (send_to_ia(server, id, "%d\n", nb_slot));
}

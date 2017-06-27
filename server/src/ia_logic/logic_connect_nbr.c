/*
** logic_connect_nbr.c for zappy in server
**
** Made by Edouard
** Login   <edouard@epitech.net>
**
** Started on  Tue Jun 27 17:29:36 2017 Edouard
** Last update Tue Jun 27 17:29:42 2017 Edouard
*/

#include "server/send.h"

static int	count_empty_slot(t_server *server, Team team)
{
  ID		cli;
  int		nb_slot;

  cli = 0;
  nb_slot = 0;
  while (cli < server->config.max_player * server->config.team_count)
    {
      if (server->game.clients[cli].ia.team == team &&
	  server->game.clients[cli].alive == false)
	{
	  ++nb_slot;
	}
    }
  return (nb_slot);
}

int	logic_connect_nbr(t_server *server, ID id, char *cmd)
{
  int	nb_slot;

  (void)cmd;
  nb_slot = count_empty_slot(server, server->game.clients[id].ia.team);
  return (send_to_ia(server, id, "%d\n", nb_slot));
}

//
// Created by puilla_e on 09/06/17.
//

#include "server/send.h"

int	count_empty_slot(t_server *server, Team team)
{
  ID	cli;
  int	nb_slot;

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

int	ia_connect_nbr(t_server *server, ID id, char *cmd)
{
  int	nb_slot;

  (void)cmd;
  nb_slot = count_empty_slot(server, server->game.clients[id].ia.team);
  return (send_to_ia(server, id, "%d\n", nb_slot));
}

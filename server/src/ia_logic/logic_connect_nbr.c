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

static int 	count_eggs(t_server *server, Team team)
{
  t_egg		*egg;
  int 		nb_eggs;

  egg = server->game.eggs;
  nb_eggs = 0;
  while (egg != NULL)
    {
      if (egg->team == team)
	++nb_eggs;
      egg = egg->next;
    }
  return (nb_eggs);
}

static int	count_empty_slot(t_server *server, Team team)
{
  ID		cli;
  int		nb_slot;
  int 		nb_player;
  int 		nb_eggs;

  cli = 0;
  nb_player = 0;
  while (cli < server->game.max_slot)
    {
      if (server->game.clients[cli].ia.team == team &&
          server->game.clients[cli].alive == true)
	++nb_player;
      ++cli;
    }
  nb_eggs = count_eggs(server, team);
  if (nb_player < server->config.max_player &&
      nb_eggs <= server->config.max_player - nb_player)
    nb_slot = server->config.max_player - nb_player;
  else
    nb_slot = nb_eggs;
  return (nb_slot);
}

int	logic_connect_nbr(t_server *server, ID id, char *cmd)
{
  int	nb_slot;

  (void)cmd;
  nb_slot = count_empty_slot(server, server->game.clients[id].ia.team);
  return (send_to_ia(server, id, "%d\n", nb_slot));
}

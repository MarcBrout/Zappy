/*
** ressources_start.c.c for zappy in /home/login_p/delivery/zappy/ressources_start.c.c
**
** Made by Prenom Nom
** Login   <prenom.nom@epitech.eu>
**
** Started on  jeu. juin 29 16:44:01 2017 Prenom Nom
** Last update jeu. juin 29 16:44:01 2017 Prenom Nom
*/

#include <stdlib.h>
#include "server.h"

static void	generate_start(t_server *server, Object type)
{
  size_t	x;
  size_t	y;

  if (rand() % 100 < 60)
    {
      x = rand() % server->game.width;
      y = rand() % server->game.height;
      ++server->game.map[x + y * server->game.width].objects[type];
      ++server->game.object_tot[type];
    }
}

void		generate_ressources_start(t_server *server)
{
  Object	j = 0;
  int 		i = 0;

  while (i < server->config.team_count * server->config.max_player)
    {
      generate_start(server, j);
      ++i;
    }
  i = 0;
  ++j;
  while (i < server->config.team_count)
    {
      while (j < OBJ_COUNT)
	{
	  generate_start(server, j);
	  ++j;
	}
      ++i;
    }
}
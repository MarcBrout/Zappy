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
#include "server/gui_commands.h"
#include "server/ia_commands.h"
#include "server.h"

static t_luck		drop_rates[OBJ_COUNT] =
 {
  {FOOD, 100},
  {LINEMATE, 42},
  {DERAUMERE, 23},
  {SIBUR, 34},
  {MENDIANE, 13},
  {PHIRAS, 21},
  {THYSTAME, 2}
 };

int		push_value(t_server *server, Object type, bool start)
{
  t_position	pos;

  pos.x = rand() % server->game.width;
  pos.y = rand() % server->game.height;
  while (!start && type != FOOD && is_incantation(server, &pos))
    {
      pos.x = rand() % server->game.width;
      pos.y = rand() % server->game.height;
    }
  ++server->game.map[pos.x + pos.y * server->game.width].objects[type];
  ++server->game.object_tot[type];
  if (!start)
    return (send_case_content(server, pos.x, pos.y));
  return (0);
}

void		generate_ressources_start(t_server *server)
{
  Object	j = 0;
  int 		i = 0;

  while (i < server->config.team_count * server->config.max_player)
    {
      push_value(server, j, true);
      ++i;
    }
  ++j;
  while (j < OBJ_COUNT)
    {
      i = 0;
      while (i < drop_rates[j].value / 4)
	{
	  push_value(server, j, true);
	  ++i;
	}
      ++j;
    }
}
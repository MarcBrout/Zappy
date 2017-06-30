/*
** resources_generator.c for zappy in server/src/game_logic
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Tue Jun 27 17:12:53 2017 brout_m
** Last update Tue Jun 27 17:15:24 2017 puilla_e
*/

#include <unistd.h>
#include <stdlib.h>
#include "server/gui_events.h"
#include "server/gui_commands.h"
#include "server/ia_commands.h"

static t_luck		drop_rates[OBJ_COUNT] =
  {
    {FOOD, 0.5},
    {LINEMATE, 0.36},
    {DERAUMERE, 0.36},
    {SIBUR, 0.41},
    {MENDIANE, 0.5},
    {PHIRAS, 0.37},
    {THYSTAME, 0.16}
  };

static void	kill_client(t_server *server, t_client *client)
{
  Object	obj = 0;

  while (obj < OBJ_COUNT)
    {
      server->game.object_tot[obj] -= client->ia.inventory[obj];
      ++obj;
    }
  ia_death(server, client->id, "");
  client->alive = false;
  client->died = true;
  --server->config.teams[client->ia.team].memberCount;
  decrement_team_count(server, client->ia.team);
}

static uint32_t		check_deads(t_server *server,
				    t_client *clients,
				    int size)
{
  int			i = 0;
  uint32_t		alive = 0;
  t_client		*client = NULL;

  while (i < size)
    {
      client = &clients[i];
      if (client->alive)
	{
	  if (client->ia.life_unit == 0)
	    {
	      client->ia.life_unit = LIFE_UNIT_MAX;
	      --client->ia.inventory[FOOD];
	    }
	  --client->ia.life_unit;
	  if (client->ia.inventory[FOOD] == 0 && client->ia.life_unit == 0)
	    kill_client(server, client);
	  else
	    ++alive;
	}
      ++i;
    }
  return (alive);
}

static int	generate(t_server *server,
			 t_luck const *luck,
			 uint32_t alive)
{
  t_position	pos;

  if (server->game.object_tot[luck->type] <
      luck->value * server->game.max_slot &&
      rand() % 100 < luck->value * (double)alive)
    {
      pos.x = rand() % server->game.width;
      pos.y = rand() % server->game.height;
      while (luck->type != FOOD && is_incantation(server, &pos))
	{
	  pos.x = rand() % server->game.width;
	  pos.y = rand() % server->game.height;
	}
      ++server->game.map[pos.x + pos.y * server->game.width].objects[luck->type];
      ++server->game.object_tot[luck->type];
      return (send_case_content(server, pos.x, pos.y));
    }
  return (0);
}

static int	generate_resources(t_server *server, uint32_t alive)
{
  uint16_t	j = 0;

  while (j < OBJ_COUNT)
    {
      if (generate(server, &drop_rates[j], alive))
	return (1);
      ++j;
    }
  return (0);
}

int		proceed_one_turn(t_server *server)
{
  uint32_t	alive;

  alive = check_deads(server, server->game.clients, server->game.max_slot);
  return (generate_resources(server, alive));
}

/*
** resources_generator.c for zappy in server/src/game_logic
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Tue Jun 27 17:12:53 2017 brout_m
** Last update Sun Jul  2 15:38:33 2017 Edouard
*/

#include <unistd.h>
#include <stdlib.h>
#include "server/gui_events.h"
#include "server/gui_commands.h"
#include "server/ia_commands.h"

static t_luck	drop_rates[OBJ_COUNT] =
  {
    {FOOD, 80},
    {LINEMATE, 42},
    {DERAUMERE, 23},
    {SIBUR, 34},
    {MENDIANE, 13},
    {PHIRAS, 21},
    {THYSTAME, 4}
  };

static void	kill_client(t_server *server, t_client *client)
{
  Object	obj = 0;
  int 		i;

  while (obj < OBJ_COUNT)
    {
      i = 0;
      while (i < client->ia.inventory[obj])
	{
	  push_value(server, obj, false);
	  --server->game.object_tot[obj];
	  ++i;
	}
      ++obj;
    }
  ia_death(server, client->id, "");
  client->alive = false;
  client->died = true;
  --server->config.teams[client->ia.team].memberCount;
  decrement_team_count(server, client->ia.team);
}

static uint32_t	check_deads(t_server *server,
			    t_client *clients,
			    int size)
{
  int		i = 0;
  uint32_t	alive = 0;
  t_client	*client = NULL;

  while (i < size)
    {
      client = &clients[i];
      if (client->alive)
	{
	  if (client->ia.life_unit == 0)
	    {
	      client->ia.life_unit = LIFE_UNIT_MAX;
	      --client->ia.inventory[FOOD];
	      send_player_inventory(server, client->id);
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
			 size_t max)
{
  if (server->game.object_tot[luck->type] < (int) max &&
      rand() % 100 < luck->value)
    {
      return (push_value(server, luck->type, false));
    }
  return (0);
}

static int	generate_resources(t_server *server, uint32_t alive)
{
  ID 		cli = 0;
  size_t 	max;
  Object	obj;

  while (cli < (int) alive)
    {
      max = server->config.team_count *
	    server->game.width * server->game.height / 2;
      generate(server, &drop_rates[0], max);
      obj = rand() % (OBJ_COUNT - 1) + 1;
      max = drop_rates[obj].value * server->config.team_count;
      generate(server, &drop_rates[obj], max);
      ++cli;
    }
  return (0);
}

int		proceed_one_turn(t_server *server)
{
  uint32_t	alive;

  alive = check_deads(server, server->game.clients, server->game.max_slot);
  return (generate_resources(server, alive));
}

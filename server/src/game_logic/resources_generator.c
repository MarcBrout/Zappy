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
    {FOOD, 80},
    {LINEMATE, 42},
    {DERAUMERE, 23},
    {SIBUR, 34},
    {MENDIANE, 13},
    {PHIRAS, 21},
    {THYSTAME, 2}
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
			 uint32_t alive,
			 size_t max)
{
  (void) alive;
  if (server->game.object_tot[luck->type] < (int) max &&
      rand() % 100 < luck->value)
    {
      return (push_value(server, luck->type, false));
    }
  return (0);
}

static int	generate_resources(t_server *server, uint32_t alive)
{
  uint16_t	j = 0;
  ID 		cli = 0;
  size_t 	max;

  while (j < OBJ_COUNT)
    {
      cli = 0;
      if (j == 0)
	max = alive * server->game.width * server->game.height / 2;
      else
	max = drop_rates[j].value * server->config.team_count;
      while (cli < (int) alive)
	{
	  if (generate(server, &drop_rates[j], alive, max))
	    return (1);
	  ++cli;
	}
      j = j + 1;
    }
  return (0);
}

int		proceed_one_turn(t_server *server)
{
  uint32_t	alive;

  alive = check_deads(server, server->game.clients, server->game.max_slot);
  return (generate_resources(server, alive));
}

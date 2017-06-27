/*
** resources_generator.c for zappy in server/src/game_logic
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Tue Jun 27 17:12:53 2017 brout_m
** Last update Tue Jun 27 17:15:24 2017 brout_m
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

static uint32_t	check_deads(t_server *server, t_client *clients, int size)
{
  int			i = 0;
  uint32_t		alive = 0;
  t_client		*client = NULL;

  while (i < size)
    {
      client = &clients[i];
      if (clients->alive)
	{
	  if (clients->ia.inventory[FOOD] - 1 == 0)
	    {
	      ia_death(server, i, "");
	      event_pdi(server, i);
	      client->alive = false;
	    }
	  else
	    {
	      ++alive;
              --clients->ia.inventory[FOOD];
	    }
	}
      ++i;
    }
  return (alive);
}

static int		generate(t_server *server,
				 t_luck const *luck,
				 uint32_t alive)
{
  size_t		x;
  size_t		y;

  if (rand() % 100 < luck->value * (double)alive)
    {
      x = rand() % server->game.width;
      y = rand() % server->game.height;
      ++server->game.map[x + y * server->game.width].objects[luck->type];
      return (send_case_content(server, (int)x, (int)y));
    }
  return (0);
}

static int		generate_resources(t_server *server, uint32_t alive)
{
  uint16_t		j = 0;

  while (j < OBJ_COUNT)
    {
      if (generate(server, &drop_rates[j], alive))
	return (1);
      ++j;
    }
  return (0);
}

int			proceed_one_turn(t_server *server)
{
  uint32_t		alive;

  alive = check_deads(server, server->game.clients, server->game.max_slot);
  return (generate_resources(server, alive));
}

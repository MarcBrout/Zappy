/*
** logic_inventory.c for zappy in server
**
** Made by Edouard
** Login   <edouard@epitech.net>
**
** Started on  Tue Jun 27 17:31:15 2017 Edouard
** Last update Tue Jun 27 18:20:53 2017 brout_m
*/

#include "server.h"
#include "server/logic_commands.h"

static const char *obj_tab[OBJ_COUNT] =
  {
    "food",
    "linemate",
    "deraumere",
    "sibur",
    "mendiane",
    "phiras",
    "thystame"
  };

int		logic_inventory(t_server *server, ID id, char *cmd)
{
  Object	obj;
  t_client	*client;

  (void) cmd;
  obj = FOOD;
  client = &server->game.clients[id];
  send_to_ia(server, id, "[%s %d", obj_tab[obj],
	     client->ia.inventory[obj]);
  ++obj;
  while (obj < THYSTAME)
    {
      send_to_ia(server, id, ",%s %d",
		 obj_tab[obj], client->ia.inventory[obj]);
      ++obj;
    }
  send_to_ia(server, id, ",%s %d]\n", obj_tab[obj],
	     client->ia.inventory[obj]);
  return (0);
}

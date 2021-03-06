/*
** logic_take_set.c for zappy in server
**
** Made by Edouard
** Login   <edouard@epitech.net>
**
** Started on  Tue Jun 27 17:32:35 2017 Edouard
** Last update Sun Jul  2 16:08:08 2017 brout_m
*/

#include <string.h>
#include "server/gui_commands.h"
#include "server/gui_events.h"

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

static Object	object_to_enum(char *obj_str)
{
  Object	obj;

  obj = FOOD;
  while (obj < OBJ_COUNT)
    {
      if (strcmp(obj_tab[obj], obj_str) == 0)
	return (obj);
      ++obj;
    }
  return (OBJ_COUNT);
}

static void	update_cell(t_server *server, ID id, Object obj, bool take)
{
  if (take)
    event_pgt(server, id, obj);
  else
    event_pdr(server, id, obj);
  send_player_inventory(server, id);
  send_case_content(server, server->game.clients[id].ia.pos.x,
		    server->game.clients[id].ia.pos.y);
}

int		logic_take(t_server *server, ID id, char *cmd)
{
  Object	obj;
  char		*obj_str;
  int		pos;

  strtok(cmd, " ");
  pos = FIND_POS(server->game.clients[id].ia.pos.x,
		 server->game.clients[id].ia.pos.y,
		 server->config.width);
  if ((obj_str = strtok(NULL, " ")) == NULL ||
      (obj = object_to_enum(obj_str)) == OBJ_COUNT)
    {
      strncircular(&server->game.clients[id].w, "ko\n", strlen("ko\n"));
      return (0);
    }
  if (server->game.map[pos].objects[obj] > 0)
    {
      --server->game.map[pos].objects[obj];
      ++server->game.clients[id].ia.inventory[obj];
      server->game.object_tot[obj] -= obj == FOOD ? 1 : 0;
      update_cell(server, id, obj, true);
      strncircular(&server->game.clients[id].w, "ok\n", strlen("ok\n"));
    }
  else
    strncircular(&server->game.clients[id].w, "ko\n", strlen("ko\n"));
  return (0);
}

int		logic_set(t_server *server, ID id, char *cmd)
{
  Object	obj;
  char		*obj_str;

  strtok(cmd, " ");
  if ((obj_str = strtok(NULL, " ")) == NULL ||
      (obj = object_to_enum(obj_str)) == OBJ_COUNT)
    {
      strncircular(&server->game.clients[id].w, "ko\n", strlen("ko\n"));
      return (0);
    }
  if (server->game.clients[id].ia.inventory[obj] > 0)
    {
      --server->game.clients[id].ia.inventory[obj];
      ++server->game.map[FIND_POS(server->game.clients[id].ia.pos.x,
				  server->game.clients[id].ia.pos.y,
				  server->config.width)].objects[obj];
      server->game.object_tot[obj] += obj == FOOD ? 1 : 0;
      update_cell(server, id, obj, false);
      strncircular(&server->game.clients[id].w, "ok\n", strlen("ok\n"));
    }
  else
    strncircular(&server->game.clients[id].w, "ko\n", strlen("ko\n"));
  return (0);
}

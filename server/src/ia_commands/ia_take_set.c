//
// Created by puilla_e on 09/06/17.
//

#include <string.h>
#include "server.h"

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

int		ia_take(t_server *server, ID id, char *cmd)
{
  Object	obj;
  char 		*obj_str;

  strtok(cmd, " ");
  if ((obj_str = strtok(NULL, " ")) == NULL ||
      (obj = object_to_enum(obj_str)) == OBJ_COUNT)
    {
      strncircular(&server->game.clients[id].w, "ko\n", strlen("ko\n"));
      return (0);
    }
  if (server->game.map[FIND_POS(server->game.clients[id].ia.pos.x,
				server->game.clients[id].ia.pos.y,
				server->config.width)].objects[obj] > 0)
    {
      --server->game.map->objects[FIND_POS(server->game.clients[id].ia.pos.x,
					   server->game.clients[id].ia.pos.y,
					   server->config.width)];
      ++server->game.clients[id].ia.inventory[obj];
      strncircular(&server->game.clients[id].w, "ok\n", strlen("ok\n"));
    }
  else
    strncircular(&server->game.clients[id].w, "ko\n", strlen("ko\n"));
  return (0);
}

int		ia_set(t_server *server, ID id, char *cmd)
{
  Object	obj;
  char 		*obj_str;

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
      strncircular(&server->game.clients[id].w, "ok\n", strlen("ok\n"));
    }
  else
    strncircular(&server->game.clients[id].w, "ko\n", strlen("ko\n"));
  return (0);
}
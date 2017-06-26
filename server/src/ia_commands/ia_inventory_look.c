//
// Created by puilla_e on 09/06/17.
//

#include <string.h>
#include "server/ia_commands.h"
#include "server/send.h"

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

int		ia_inventory(t_server *server, ID id, char *cmd)
{
  Object	obj;
  t_client	*client;

  (void) cmd;
  obj = FOOD;
  client = &server->game.clients[id];
  send_to_ia(server, id, "[%s %d", obj_tab[obj], client->ia.inventory[obj]);
  ++obj;
  while (obj < THYSTAME)
    {
      send_to_ia(server, id, ",%s %d", obj_tab[obj], client->ia.inventory[obj]);
      ++obj;
    }
  send_to_ia(server, id, ",%s %d]\n", obj_tab[obj], client->ia.inventory[obj]);
  return (0);
}

static bool	look_tile_player(t_server *server,
				 t_client *client,
				 t_position *pos)
{
  ID		cli;
  bool		space;

  cli = 0;
  space = false;
  while (cli < server->config.max_player * server->config.team_count)
    {
      if (server->game.clients[cli].alive == true &&
	  server->game.clients[cli].ia.pos.x == pos->x &&
	  server->game.clients[cli].ia.pos.y == pos->y)
	{
	  if (space)
	    strncircular(&client->w, " player", strlen(" player"));
	  else
	    strncircular(&client->w, "player", strlen("player"));
	  space = true;
	}
    }
  return (space);
}

static void	look_tile(t_server *server, t_client *client, t_position *pos)
{
  Object	obj;
  int 		i;
  int 		tile;
  bool		space;

  tile = FIND_POS(pos->x, pos->y, server->config.width);
  space = look_tile_player(server, client, pos);
  obj = FOOD;
  while (obj < OBJ_COUNT)
    {
      i = 0;
      while (i < server->game.map[tile].objects[obj])
	{
	  if (space)
	    send_to_ia(server, client->id, " %s", obj_tab[obj]);
	  else
	    send_to_ia(server, client->id, "%s", obj_tab[obj]);
	  space = true;
	  ++i;
	}
      ++obj;
    }
}

static Direction change_dir(Direction src, bool left)
{
  if (left == true)
    {
      if (src == NORTH)
	return (WEST);
      return (src - 1);
    }
  if (src == WEST)
    return (NORTH);
  return (src + 1);
}

int		ia_look(t_server *server, ID id, char *cmd)
{
  t_client	*client;
  t_position	pos;
  int 		i;
  int 		j;

  client = &server->game.clients[id];
  strncircular(&client->w, "[", strlen("]"));
  pos = client->ia.pos;
  while (i <= client->ia.level)
    {
      j = 0;
      while (j < 2 * i + 1)
	{
	  if (i != 0)
	    strncircular(&client->w, ",", strlen(","));
	  look_tile(server, client, &pos);
	  if (j != 2 * i)
	    forward_pos(server, &pos, change_dir(client->ia.dir, false), 1);
	  ++j;
	}
      ++i;
      forward_pos(server, &pos, client->ia.dir, 1);
      forward_pos(server, &pos, change_dir(client->ia.dir, true), i + i - 1);
    }
  strncircular(&client->w, "]", strlen("]"));
  return (0);
}
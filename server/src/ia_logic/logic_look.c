/*
** logic_look.c for zappy in server
**
** Made by Edouard
** Login   <edouard@epitech.net>
**
** Started on  Tue Jun 27 17:31:57 2017 Edouard
** Last update Sun Jul  2 19:14:40 2017 Edouard
*/

#include <string.h>
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

static bool	look_tile_player(t_server *server,
				    t_client *client,
				    t_position *pos)
{
  ID		cli;
  bool		space;

  cli = 0;
  space = false;
  while (cli < server->game.max_slot)
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
      ++cli;
    }
  return (space);
}

static void	look_tile(t_server *server, t_client *client, t_position *pos)
{
  Object	obj;
  int		i;
  int		tile;
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

static	void	look_print_line(t_server *server,
				t_client *client,
				t_position *pos,
				int len_line)
{
  int		j;

  j = 0;
  while (j < 2 * len_line + 1)
    {
      if (len_line != 0)
	strncircular(&client->w, ",", strlen(","));
      look_tile(server, client, pos);
      if (j != 2 * len_line)
	forward_pos(server, pos, change_dir(client->ia.dir, false), 1);
      ++j;
    }
}

int		logic_look(t_server *server, ID id, char *cmd)
{
  t_client	*client;
  t_position	pos;
  int		i;

  (void) cmd;
  client = &server->game.clients[id];
  strncircular(&client->w, "[", strlen("["));
  pos = client->ia.pos;
  i = 0;
  while (i <= (int) client->ia.level)
    {
      look_print_line(server, client, &pos, i);
      ++i;
      forward_pos(server, &pos, client->ia.dir, 1);
      forward_pos(server, &pos, change_dir(client->ia.dir, true), i);
    }
  strncircular(&client->w, "]\n", strlen("]\n"));
  return (0);
}

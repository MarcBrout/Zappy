/*
** logic_incantation_start.c for zappy in server
**
** Made by Edouard
** Login   <edouard@epitech.net>
**
** Started on  Tue Jun 27 17:30:59 2017 Edouard
** Last update Tue Jun 27 17:31:04 2017 Edouard
*/

#include <string.h>
#include "server/gui_events.h"
#include "server/ia_commands.h"

static const int incant_tab[MAX_INCANT][OBJ_COUNT] =
 {
  {1, 1, 0, 0, 0, 0, 0},
  {2, 1, 1, 1, 0, 0, 0},
  {2, 2, 0, 1, 0, 2, 0},
  {4, 1, 1, 2, 0, 1, 0},
  {4, 1, 2, 1, 3, 0, 0},
  {6, 1, 2, 3, 0, 1, 0},
  {6, 2, 2, 2, 2, 2, 1}
 };

static void	send_incantation_start(t_server *server,
				       t_client *client,
				       int max_player)
{
  ID 		cli;
  int 		nb_player;
  int 		len;

  cli = 0;
  nb_player = 1;
  len = strlen("Elevation underway\n");
  while (nb_player < max_player &&
	 cli < server->game.max_slot)
    {
      if (server->game.clients[cli].alive &&
	  server->game.clients[cli].ia.pos.x == client->ia.pos.x &&
	  server->game.clients[cli].ia.pos.y == client->ia.pos.y)
	{
	  strncircular(&server->game.clients[cli].w,
		       "Elevation underway\n",
		       len);
	  ++nb_player;
	}
      ++cli;
    }
}

static int	count_player(t_server *server,
			       t_client *client)
{
  ID 		cli;
  int 		nb_player;

  cli = 0;
  nb_player = 0;
  while (cli < server->game.max_slot)
    {
      if (server->game.clients[cli].alive &&
	  server->game.clients[cli].ia.pos.x == client->ia.pos.x &&
	  server->game.clients[cli].ia.pos.y == client->ia.pos.y)
	{
	  if (server->game.clients[cli].ia.level == client->ia.level)
	    ++nb_player;
	  else
	    return (-1);
	}
      ++cli;
    }
  return (nb_player);
}

int	check_incantation(t_server *server, ID id,
			     t_client *client, t_cell *cell)
{
  Object	obj;

  if (incant_tab[client->ia.level - 1][0] != count_player(server, client))
    {
      strncircular(&client->w, "ko\n", strlen("ko\n"));
      return (1);
    }
  obj = LINEMATE;
  while (obj < OBJ_COUNT)
    {
      if (incant_tab[client->ia.level - 1][obj] != cell->objects[obj])
	{
	  strncircular(&server->game.clients[id].w, "ko\n", strlen("ko\n"));
	  return (1);
	}
      ++obj;
    }
  return (0);
}

int		logic_incantation_start(t_server *server, ID id, char *cmd)
{
  t_client	*client;
  t_cell	*cell;
  int 		ret;

  (void)cmd;
  client = &server->game.clients[id];
  cell = &server->game.map[FIND_POS(client->ia.pos.x,
				    client->ia.pos.y,
				    server->config.width)];
  if (check_incantation(server, id, client, cell) == 1)
    return (0);
  event_pic(server, client);
  send_incantation_start(server, client, incant_tab[client->ia.level][0]);
  ret = store_command_sequel(&server->game.clients[id].store,
			     "Incantation",
			     300);
  return (ret == 1 ? 1 : 0);
}

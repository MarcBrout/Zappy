/*
** logic_incantation.c for zappy in server
**
** Made by Edouard
** Login   <edouard@epitech.net>
**
** Started on  Tue Jun 27 17:30:41 2017 Edouard
** Last update Tue Jun 27 17:30:47 2017 Edouard
*/

#include "server/logic_commands.h"
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

static int	send_incantation_end(t_server *server,
				     t_client *client,
				     int max_player)
{
  ID 		cli;
  int 		nb_player;

  cli = 0;
  nb_player = 1;
  ++client->ia.level;
  //TODO GUI add event plv (level of player)
  send_to_ia(server, client->id, "Current level: %u\n", client->ia.level);
  while (nb_player < max_player &&
   	 cli < server->game.max_slot)
    {
      if (server->game.clients[cli].alive && cli != client->sock &&
	  server->game.clients[cli].ia.pos.x == client->ia.pos.x &&
	  server->game.clients[cli].ia.pos.y == client->ia.pos.y)
	{
	  ++server->game.clients[cli].ia.level;
	  //TODO GUI add event plv (level of player)
	  send_to_ia(server, cli, "Current level: %u\n",
		     server->game.clients[cli].ia.level);
	  ++nb_player;
	}
      ++cli;
    }
  return (0);
}

int		logic_incantation(t_server *server, ID id, char *cmd)
{
  t_client	*client;
  t_cell	*cell;
  Object	obj;

  (void)cmd;
  client = &server->game.clients[id];
  cell = &server->game.map[FIND_POS(client->ia.pos.x,
				    client->ia.pos.y,
				    server->config.width)];
  if (check_incantation(server, id, client, cell) == 1)
    {
      event_pie(server, &client->ia.pos, 0);
      return (0);
    }
  event_pie(server, &client->ia.pos, 1);
  obj = LINEMATE;
  while (obj < OBJ_COUNT)
    {
      cell->objects[obj] -= incant_tab[client->ia.level][obj];
      ++obj;
    }
  //TODO GUI add event bct (resources used on tile)
  return (send_incantation_end(server, client,
			       incant_tab[client->ia.level][0]));
}

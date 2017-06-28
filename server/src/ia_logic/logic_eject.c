/*
** logic_eject.c for zappy in server
**
** Made by Edouard
** Login   <edouard@epitech.net>
**
** Started on  Tue Jun 27 17:28:29 2017 Edouard
** Last update Tue Jun 27 17:28:36 2017 Edouard
*/

#include <string.h>
#include <server/gui_commands.h>
#include "server/gui_events.h"
#include "server/direction_manager.h"
#include "server/logic_commands.h"

static int	send_eject_to_player(t_server *server, t_client *client)
{
  ID		cli;

  cli = 0;
  while (cli < server->game.max_slot)
    {
      if (server->game.clients[cli].alive == true &&
	  server->game.clients[cli].ia.pos.x == client->ia.pos.x &&
	  server->game.clients[cli].ia.pos.y == client->ia.pos.y &&
	  cli != client->id)
	{
	  forward_pos(server,
		      &server->game.clients[cli].ia.pos,
		      client->ia.dir,
		      1);
	  send_to_ia(server, server->game.clients[cli].sock,
		     "eject: %d\n",
		     find_direction(server,
				    &client->ia.pos,
				    &server->game.clients[cli].ia.pos,
				    server->game.clients[cli].ia.dir));
	  send_player_position(server, cli);
	}
      ++cli;
    }
  return (0);
}

static bool	check_if_player(t_server *server, t_client *client)
{
  ID		cli;

  cli = 0;
  while (cli < server->game.max_slot)
    {
      if (server->game.clients[cli].alive == true &&
	  server->game.clients[cli].ia.pos.x == client->ia.pos.x &&
	  server->game.clients[cli].ia.pos.y == client->ia.pos.y &&
	  &server->game.clients[cli] != client)
	{
	  return (true);
	}
    }
  return (false);
}

int		logic_eject(t_server *server, ID id, char *cmd)
{
  t_client	*client;

  (void)cmd;
  client = &server->game.clients[id];
  if (check_if_player(server, client))
    {
      event_pex(server, id);
      strncircular(&client->w, "ok\n", strlen("ok\n"));
      return (send_eject_to_player(server, client));
    }
  strncircular(&client->w, "ko\n", strlen("ko\n"));
  return (0);
}

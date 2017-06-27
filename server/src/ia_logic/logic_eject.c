//
// Created by puilla_e on 09/06/17.
//

#include <string.h>
#include "server/send.h"
#include "server/direction_manager.h"
#include "server/logic_commands.h"

static int	send_eject_to_player(t_server *server, t_client *client)
{
  ID		cli;

  cli = 0;
  while (cli < server->config.max_player * server->config.team_count)
    {
      if (server->game.clients[cli].alive == true &&
	  server->game.clients[cli].ia.pos.x == client->ia.pos.x &&
	  server->game.clients[cli].ia.pos.y == client->ia.pos.y &&
	  &server->game.clients[cli] != client)
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
	}
      ++cli;
    }
  return (0);
}

static bool	check_if_player(t_server *server, t_client *client)
{
  ID		cli;

  cli = 0;
  while (cli < server->config.max_player * server->config.team_count)
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
      strncircular(&client->w, "ok\n", strlen("ok\n"));
      return (send_eject_to_player(server, client));
    }
  strncircular(&client->w, "ko\n", strlen("ko\n"));
  return (0);
}
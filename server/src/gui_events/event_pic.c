//
// Created by brout_m on 23/06/17.
//

#include "server.h"

int event_pic(t_server *server, t_client const *incantor)
{
  t_position pos = incantor->ia.pos;
  t_client * client;
  int        i = 0;

  if (send_to_gui(server, "pic %d %d %d %d", pos.x, pos.y, incantor->ia.level,
                  incantor->id))
    return (1);
  while (i < server->config.max_player * server->config.team_count)
    {
      client = &server->game.clients[i];
      if (client->ia.pos.x == pos.x && client->ia.pos.y == pos.y &&
          client->ia.level == incantor->ia.level)
	{
	  if (send_to_gui(server, " %d", client->ia))
	    return (1);
	}
      ++i;
    }
  send_to_gui(server, "\n");
  return (0);
}
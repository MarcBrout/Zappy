//
// Created by brout_m on 23/06/17.
//

#include "server.h"

int event_pic(t_server *server, t_client const *incantor)
{
  t_position pos = incantor->ia.pos;
  t_client * client;
  int        i = 0;

  log_this("[PIC] Incantation level '%d' started on:\n\tx: %d\n\ty: %d\n "
               "with :\n\t%d",
           incantor->ia.level, pos.x, pos.y, incantor->id);
  if (send_to_gui(server, "pic %d %d %d %d", pos.x, pos.y, incantor->ia.level,
                  incantor->id))
    return (1);
  while (i < server->config.max_player * server->config.team_count)
    {
      client = &server->game.clients[i];
      if (client->ia.pos.x == pos.x && client->ia.pos.y == pos.y &&
          client->ia.level == incantor->ia.level)
	{
          log_this(" %d", client->id);
	  if (send_to_gui(server, " %d", client->id))
	    return (1);
	}
      ++i;
    }
  log_this("\n");
  send_to_gui(server, "\n");
  return (0);
}
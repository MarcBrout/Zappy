//
// Created by brout_m on 23/06/17.
//

#include "server.h"

int event_pnw(t_server *server, t_client const *newClient)
{
  log_this("[PNW] New client '%d' of team '%s' and level '%d'"
           ", facing '%d', connected on:\n\tx: %d\n\ty: %d",
           newClient->id, server->config.teams[newClient->ia.team],
           newClient->ia.level, newClient->ia.dir, newClient->ia.pos.x,
           newClient->ia.pos.y);
  return (send_to_gui(server, "pnw %d %d %d %d %d %s\n", newClient->id,
                      newClient->ia.pos.x, newClient->ia.pos.y,
                      newClient->ia.dir, newClient->ia.level,
                      server->config.teams[newClient->ia.team]));
}
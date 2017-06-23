//
// Created by brout_m on 23/06/17.
//

#include "server.h"

int event_pnw(t_server *server, t_client const *newClient)
{
  return (send_to_gui(server, "pnw %d %d %d %d %d %s\n", newClient->id,
                      newClient->ia.pos.x, newClient->ia.pos.y,
                      newClient->ia.dir, newClient->ia.level,
                      server->config.teams[newClient->ia.team]));
}
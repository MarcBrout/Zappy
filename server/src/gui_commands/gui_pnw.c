//
// Created by brout_m on 23/06/17.
//

#include "server.h"
#include "server/send.h"

int gui_pnw(t_server *server, Socket sock, t_client *newClient)
{
  return (send_to_gui(server, "pnw %d %d %d %d %d %s\n", newClient->id,
                      newClient->ia.pos.x, newClient->ia.pos.y,
                      newClient->ia.dir, newClient->ia.level,
                      newClient->ia.team));
}
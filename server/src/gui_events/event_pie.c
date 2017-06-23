//
// Created by brout_m on 23/06/17.
//

#include "server.h"

int event_pie(t_server *server, t_position const *pos, int result)
{
  log_this("[PEX] Incantation %s on:\n\tx: %d\n\ty: %d\n",
           (result ? "SUCCEEDED" : "FAILED"), pos->x, pos->y);
  return (send_to_gui(server, "pic %d %d %d\n", pos->x, pos->y, result));
}
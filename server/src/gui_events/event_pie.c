//
// Created by brout_m on 23/06/17.
//

#include "server.h"

int event_pie(t_server *server, t_position const *pos, int result)
{
  return (send_to_gui(server, "pic %d %d %d\n", pos->x, pos->y, result));
}
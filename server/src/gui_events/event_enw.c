//
// Created by brout_m on 23/06/17.
//

#include "server.h"

int event_enw(t_server *server, ID id, t_egg const *egg)
{
  return (send_to_gui(server, "enw %d %d %d %d\n", egg->id, id, egg->pos.x,
                      egg->pos.y));
}
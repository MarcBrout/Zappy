//
// Created by brout_m on 23/06/17.
//

#include "server.h"

int event_enw(t_server *server, ID id, t_egg const *egg)
{
  log_this("[ENW] Client '%d' layed egg '%d' on:\n\tx : %d\n\ty : %d\n",
           id, egg->id, egg->pos.x, egg->pos.y);
  return (send_to_gui(server, "enw %d %d %d %d\n", egg->id, id, egg->pos.x,
                      egg->pos.y));
}
//
// Created by brout_m on 23/06/17.
//

#include "server.h"

int event_pbc(t_server *server, ID id, char const *broadcast)
{
  log_this("[PBC] Client '%d' Broadcasting : %s\n", id, broadcast);
  return (send_to_gui(server, "pbc %d %s\n", id, broadcast));
}
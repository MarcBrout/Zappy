//
// Created by brout_m on 23/06/17.
//

#include "server.h"

int event_pdr(t_server *server, ID id, enum e_object obj)
{
  log_this("[PDR] Client '%d' threw %s\n", id, nameof(obj));
  return (send_to_gui(server, "pdr %d %d\n", id, obj));
}

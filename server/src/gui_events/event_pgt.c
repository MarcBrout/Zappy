//
// Created by brout_m on 23/06/17.
//

#include "server.h"

int event_pgt(t_server *server, ID id, enum e_object obj)
{
  return (send_to_gui(server, "pgt %d %d\n", id, obj));
}
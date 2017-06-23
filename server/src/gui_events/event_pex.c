//
// Created by brout_m on 23/06/17.
//

#include "server.h"

int event_pex(t_server *server, ID id)
{
  return (send_to_gui(server, "pex %d\n", id));
}
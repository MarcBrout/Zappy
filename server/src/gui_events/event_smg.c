//
// Created by brout_m on 23/06/17.
//

#include "server.h"

int event_smg(t_server *server, char const *smg)
{
  return (send_to_gui(server, "smg %s\n", smg));
}
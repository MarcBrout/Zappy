//
// Created by brout_m on 23/06/17.
//

#include "server.h"

int event_ebo(t_server *server, ID eggId)
{
  log_this("[EBO] Client connected on egg '%d'\n", eggId);
  return (send_to_gui(server, "ebo %d\n", eggId));
}
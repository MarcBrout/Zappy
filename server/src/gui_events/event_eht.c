//
// Created by brout_m on 23/06/17.
//

#include "server.h"

int event_eht(t_server *server, ID id)
{
  log_this("[EHT] Egg '%d' Hatched\n", id);
  return (send_to_gui(server, "eht %d\n", id));
}
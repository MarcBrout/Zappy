//
// Created by brout_m on 23/06/17.
//

#include "server.h"

int event_edi(t_server *server, ID id)
{
  log_this("[EDI] Egg '%d' starved to death\n", id);
  return (send_to_gui(server, "edi %d\n", id));
}
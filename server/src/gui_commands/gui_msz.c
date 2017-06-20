//
// Created by brout_m on 12/06/17.
//

#include "server/send.h"

int gui_msz(t_server *server, ID id, char *cmd)
{
  (void)cmd;
  (void)id;
  return (send_to_gui(server, "msz %d %d\n",
                      server->config.width,
                      server->config.height));
}
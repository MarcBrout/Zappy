//
// Created by brout_m on 09/06/17.
//

#include "server.h"

int gui_unknown(t_server *server, t_client *client, char *cmd)
{
  (void)client;
  (void)cmd;
  log_this("GUI send unknown command\n");
  return (send_to_gui(server, "suc\n"));
}
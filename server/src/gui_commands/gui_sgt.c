//
// Created by brout_m on 13/06/17.
//

#include "server.h"

int gui_sgt(t_server *server, t_client *client, char *cmd)
{
  (void)cmd;
  (void)client;
  log_this("[SGT] GUI asked Time unit : %d\n", server->config.time);
  return (send_to_gui(server, "sgt %d\n", server->config.time));
}
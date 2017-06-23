//
// Created by brout_m on 13/06/17.
//

#include "server.h"

int gui_sgt(t_server *server, Socket sock, char *cmd)
{
  (void)cmd;
  (void)sock;
  log_this("[SGT] GUI asked Time unit : %d\n", server->config.time);
  return (send_to_gui(server, "sgt %d\n", server->config.time));
}
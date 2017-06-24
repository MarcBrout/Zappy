//
// Created by brout_m on 12/06/17.
//

#include "server.h"

int gui_msz(t_server *server, t_client *client, char *cmd)
{
  (void)cmd;
  (void)client;
  log_this("[MSZ] GUI asked map size:\n\tx: %d\n\ty: %d\n",
           server->config.width, server->config.height);
  return (send_to_gui(server, "msz %d %d\n",
                      server->config.width,
                      server->config.height));
}
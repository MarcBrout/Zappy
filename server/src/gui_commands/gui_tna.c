//
// Created by brout_m on 12/06/17.
//

#include "server/send.h"

int gui_tna(t_server *server, Socket sock, char *cmd)
{
  (void)cmd;
  (void)sock;
  return (send_to_gui(server, "tna %s\n", server->config.team1) ||
          send_to_gui(server, "tna %s\n", server->config.team2));
}
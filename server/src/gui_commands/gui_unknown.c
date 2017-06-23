//
// Created by brout_m on 09/06/17.
//

#include <string.h>
#include "server.h"

int gui_unknown(t_server *server, Socket sock, char *cmd)
{
  (void)cmd;
  log_this("GUI send unknown command\n");
  strncircular(&server->game.clients[sock].w, "suc\n", strlen("suc\n"));
  return (0);
}
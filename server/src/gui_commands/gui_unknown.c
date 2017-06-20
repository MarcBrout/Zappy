//
// Created by brout_m on 09/06/17.
//

#include <string.h>
#include "server.h"

int gui_unknown(t_server *server, ID id, char *cmd)
{
  (void)cmd;
  strncircular(&server->game.clients[id].w, "suc\n", strlen("suc\n"));
  return (0);
}
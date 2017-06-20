//
// Created by brout_m on 09/06/17.
//

#include <string.h>
#include "server/server_data.h"

int ia_unknown(t_server *server, ID id, char *cmd)
{
  (void)cmd;
  strncircular(&server->game.clients[id].w, "ko\n", strlen("ko\n"));
  return (0);
}

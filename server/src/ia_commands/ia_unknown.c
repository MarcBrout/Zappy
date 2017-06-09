//
// Created by brout_m on 09/06/17.
//

#include <string.h>
#include "server/server_data.h"

int ia_unknown(t_server *server, Socket sock, char *cmd)
{
  (void)cmd;
  strncircular(&server->game.clients[sock].w, "ko\n", strlen("ko\n"));
  return (0);
}

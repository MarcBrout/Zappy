//
// Created by puilla_e on 09/06/17.
//

#include <string.h>
#include "server/server_data.h"

int	ia_left(t_server *server, Socket sock, char *cmd)
{
  //TODO add time management
  (void)cmd;
  server->game.clients[sock].ia.dir =
   server->game.clients[sock].ia.dir == NORTH ? WEST :
   server->game.clients[sock].ia.dir - 1;
  strncircular(&server->game.clients[sock].w, "ok\n", strlen("ok\n"));
  return (0);
}

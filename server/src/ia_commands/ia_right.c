//
// Created by puilla_e on 09/06/17.
//

#include <string.h>
#include "server/server_data.h"

int	ia_right(t_server *server, ID id, char *cmd)
{
  //TODO add time management
  (void)cmd;
  server->game.clients[id].ia.dir =
   server->game.clients[id].ia.dir == WEST ? NORTH :
   server->game.clients[id].ia.dir + 1;
  strncircular(&server->game.clients[id].w, "ok\n", strlen("ok\n"));
  return (0);
}
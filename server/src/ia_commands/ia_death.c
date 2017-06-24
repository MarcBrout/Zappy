//
// Created by puilla_e on 09/06/17.
//

#include <string.h>
#include "server.h"

int 	ia_death(t_server *server, ID id, char *cmd)
{
  (void) cmd;
  strncircular(&server->game.clients[id].w, "death\n", strlen("death\n"));
  return (0);
}
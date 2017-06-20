//
// Created by puilla_e on 09/06/17.
//

#include <string.h>
#include "server/server_data.h"
#include "server/eggs.h"

int	ia_fork(t_server *server, ID id, char *cmd)
{
  (void)cmd;
//TODO add time management
  if (add_egg(server, &server->game.clients[id].ia.pos,
	      server->game.clients[id].ia.team))
    return (1);
  strncircular(&server->game.clients[id].w, "ok\n", strlen("ok\n"));
  return (0);
}

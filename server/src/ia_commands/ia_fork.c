//
// Created by puilla_e on 09/06/17.
//

#include <string.h>
#include "server/server_data.h"
#include "server/eggs.h"

int	ia_fork(t_server *server, Socket sock, char *cmd)
{
  (void)cmd;
//TODO add time management
  if (add_egg(server, &server->game.clients[sock].ia.pos,
	      server->game.clients[sock].ia.team))
    return (1);
  strncircular(&server->game.clients[sock].w, "ok\n", strlen("ok\n"));
  return (0);
}

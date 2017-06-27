//
// Created by puilla_e on 09/06/17.
//

#include "server/ia_commands.h"

int		ia_incantation(t_server *server, ID id, char *cmd)
{
  (void) cmd;
  return (store_command(&server->game.clients[id].store,
			"IncantationStart",
			0));
}
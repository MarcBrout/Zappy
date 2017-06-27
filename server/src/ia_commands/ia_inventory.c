//
// Created by puilla_e on 09/06/17.
//

#include "server/ia_commands.h"

int		ia_inventory(t_server *server, ID id, char *cmd)
{
  return (store_command(&server->game.clients[id].store, cmd, 1));
}
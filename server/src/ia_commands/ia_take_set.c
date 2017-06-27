//
// Created by puilla_e on 09/06/17.
//

#include "server.h"

int		ia_take(t_server *server, ID id, char *cmd)
{
  return (store_command(&server->game.clients[id].store, cmd, 7));
}

int		ia_set(t_server *server, ID id, char *cmd)
{
  return (store_command(&server->game.clients[id].store, cmd, 7));
}
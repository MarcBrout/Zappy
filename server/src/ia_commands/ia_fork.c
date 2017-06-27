//
// Created by puilla_e on 09/06/17.
//

#include "server/server_data.h"

int	ia_fork(t_server *server, ID id, char *cmd)
{
  return (store_command(&server->game.clients[id].store, cmd, 42));
}

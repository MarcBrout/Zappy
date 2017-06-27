//
// Created by puilla_e on 09/06/17.
//

#include "server/server_data.h"

int	ia_right(t_server *server, ID id, char *cmd)
{
  return (store_command(&server->game.clients[id].store, cmd, 7));
}

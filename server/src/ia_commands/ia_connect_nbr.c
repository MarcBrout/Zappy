//
// Created by puilla_e on 09/06/17.
//

#include "server/send.h"

int	ia_connect_nbr(t_server *server, ID id, char *cmd)
{
  return (store_command(&server->game.clients[id].store, cmd, 0));
}

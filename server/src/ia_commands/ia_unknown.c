//
// Created by brout_m on 09/06/17.
//

#include "server.h"

int ia_unknown(t_server *server, ID id, char *cmd)
{
  return (store_command(&server->game.clients[id].store, cmd, 0));
}

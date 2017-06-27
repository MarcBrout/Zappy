//
// Created by puilla_e on 09/06/17.
//

#include "server/gui_events.h"

int	logic_fork_start(t_server *server, ID id, char *cmd)
{
  int	ret;

  (void) cmd;
  event_pfk(server, id);
  ret = store_command_sequel(&server->game.clients[id].store, "Fork", 42);
  return (ret == 1 ? 1 : 0);
}

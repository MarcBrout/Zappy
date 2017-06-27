//
// Created by puilla_e on 09/06/17.
//

#include "server/gui_events.h"
#include "server/eggs.h"

int	logic_fork(t_server *server, ID id, char *cmd)
{
  t_egg	*egg;

  (void)cmd;
  if ((egg = add_egg(server, &server->game.clients[id].ia.pos,
		     server->game.clients[id].ia.team)) == NULL)
    return (1);
  event_enw(server, id, egg);
  send_to_ia(server, id, "ok\n");
  return (0);
}

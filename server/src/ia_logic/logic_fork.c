/*
** logic_fork.c for zappy in server
**
** Made by Edouard
** Login   <edouard@epitech.net>
**
** Started on  Tue Jun 27 17:29:18 2017 Edouard
** Last update Tue Jun 27 17:29:25 2017 Edouard
*/

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

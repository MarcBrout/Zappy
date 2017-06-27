/*
** logic_fork_start.c for zappy in server
**
** Made by Edouard
** Login   <edouard@epitech.net>
**
** Started on  Tue Jun 27 17:28:55 2017 Edouard
** Last update Tue Jun 27 17:29:01 2017 Edouard
*/

#include "server/gui_events.h"

int	logic_fork_start(t_server *server, ID id, char *cmd)
{
  int	ret;

  (void) cmd;
  event_pfk(server, id);
  ret = store_command_sequel(&server->game.clients[id].store, "Fork", 42);
  return (ret == 1 ? 1 : 0);
}

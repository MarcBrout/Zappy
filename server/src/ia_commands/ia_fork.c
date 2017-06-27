/*
** ia_fork.c for zappy in server
**
** Made by Edouard
** Login   <edouard@epitech.net>
**
** Started on  Tue Jun 27 17:34:26 2017 Edouard
** Last update Tue Jun 27 17:34:33 2017 Edouard
*/

#include "server/server_data.h"

int	ia_fork(t_server *server, ID id, char *cmd)
{
  (void) cmd;
  return (store_command(&server->game.clients[id].store, "ForkStart", 42));
}

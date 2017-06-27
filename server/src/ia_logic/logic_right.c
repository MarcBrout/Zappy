/*
** logic_right.c for zappy in server
**
** Made by Edouard
** Login   <edouard@epitech.net>
**
** Started on  Tue Jun 27 17:32:14 2017 Edouard
** Last update Tue Jun 27 17:32:22 2017 Edouard
*/

#include <string.h>
#include "server/server_data.h"

int	logic_right(t_server *server, ID id, char *cmd)
{
  //TODO GUI add event ppo
  (void)cmd;
  server->game.clients[id].ia.dir =
   server->game.clients[id].ia.dir == WEST ? NORTH :
   server->game.clients[id].ia.dir + 1;
  strncircular(&server->game.clients[id].w, "ok\n", strlen("ok\n"));
  return (0);
}

/*
** ia_take_set.c for zappy in server
**
** Made by Edouard
** Login   <edouard@epitech.net>
**
** Started on  Tue Jun 27 17:37:55 2017 Edouard
** Last update Tue Jun 27 17:38:12 2017 Edouard
*/

#include "server.h"

int	ia_take(t_server *server, ID id, char *cmd)
{
  return (store_command(&server->game.clients[id].store, cmd, 7));
}

int	ia_set(t_server *server, ID id, char *cmd)
{
  return (store_command(&server->game.clients[id].store, cmd, 7));
}

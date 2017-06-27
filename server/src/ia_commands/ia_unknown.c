/*
** ia_unknown.c for zappy in server
**
** Made by Edouard
** Login   <edouard@epitech.net>
**
** Started on  Tue Jun 27 17:40:31 2017 Edouard
** Last update Tue Jun 27 17:40:37 2017 Edouard
*/

#include "server.h"

int ia_unknown(t_server *server, ID id, char *cmd)
{
  return (store_command(&server->game.clients[id].store, cmd, 0));
}

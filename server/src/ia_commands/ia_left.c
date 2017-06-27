/*
** ia_left.c for zappy in server
**
** Made by Edouard
** Login   <edouard@epitech.net>
**
** Started on  Tue Jun 27 17:36:57 2017 Edouard
** Last update Tue Jun 27 17:37:07 2017 Edouard
*/

#include "server/server_data.h"

int	ia_left(t_server *server, ID id, char *cmd)
{
  return (store_command(&server->game.clients[id].store, cmd, 7));
}

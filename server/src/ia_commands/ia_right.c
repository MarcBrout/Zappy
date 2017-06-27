/*
** ia_right.c for zappy in server
**
** Made by Edouard
** Login   <edouard@epitech.net>
**
** Started on  Tue Jun 27 17:37:40 2017 Edouard
** Last update Tue Jun 27 17:37:46 2017 Edouard
*/

#include "server/server_data.h"

int	ia_right(t_server *server, ID id, char *cmd)
{
  return (store_command(&server->game.clients[id].store, cmd, 7));
}

/*
** ia_forward.c for zappy in server
**
** Made by Edouard
** Login   <edouard@epitech.net>
**
** Started on  Tue Jun 27 17:34:43 2017 Edouard
** Last update Tue Jun 27 17:34:49 2017 Edouard
*/

#include "server/server_data.h"

int	ia_forward(t_server *server, ID id, char *cmd)
{
  return (store_command(&server->game.clients[id].store, cmd, 7));
}

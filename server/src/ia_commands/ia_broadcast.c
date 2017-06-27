/*
** ia_broadcast.c for zappy in server
**
** Made by Edouard
** Login   <edouard@epitech.net>
**
** Started on  Tue Jun 27 17:33:00 2017 Edouard
** Last update Tue Jun 27 17:33:15 2017 Edouard
*/

#include "server/send.h"

int	ia_broadcast(t_server *server, ID id, char *cmd)
{
  return (store_command(&server->game.clients[id].store, cmd, 7));
}

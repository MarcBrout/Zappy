/*
** ia_connect_nbr.c for zappy in server
**
** Made by Edouard
** Login   <edouard@epitech.net>
**
** Started on  Tue Jun 27 17:33:24 2017 Edouard
** Last update Tue Jun 27 17:33:37 2017 Edouard
*/

#include "server/send.h"

int	ia_connect_nbr(t_server *server, ID id, char *cmd)
{
  return (store_command(&server->game.clients[id].store, cmd, 0));
}

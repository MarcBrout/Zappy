/*
** ia_inventory.c for zappy in server
**
** Made by Edouard
** Login   <edouard@epitech.net>
**
** Started on  Tue Jun 27 17:36:34 2017 Edouard
** Last update Tue Jun 27 17:39:20 2017 Edouard
*/

#include "server/ia_commands.h"

int	ia_inventory(t_server *server, ID id, char *cmd)
{
  return (store_command(&server->game.clients[id].store, cmd, 1));
}

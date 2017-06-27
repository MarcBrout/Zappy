/*
** ia_look.c for zappy in server
**
** Made by Edouard
** Login   <edouard@epitech.net>
**
** Started on  Tue Jun 27 17:37:17 2017 Edouard
** Last update Tue Jun 27 17:40:11 2017 Edouard
*/

#include "server/ia_commands.h"

int	ia_look(t_server *server, ID id, char *cmd)
{
  return (store_command(&server->game.clients[id].store, cmd, 7));
}

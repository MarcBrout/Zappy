/*
** ia_incantation.c for zappy in server
**
** Made by Edouard
** Login   <edouard@epitech.net>
**
** Started on  Tue Jun 27 17:35:08 2017 Edouard
** Last update Tue Jun 27 17:39:07 2017 Edouard
*/

#include "server/ia_commands.h"

int	ia_incantation(t_server *server, ID id, char *cmd)
{
  (void) cmd;
  return (store_command(&server->game.clients[id].store,
			"IncantationStart",
			0));
}

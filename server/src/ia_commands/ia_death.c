/*
** ia_death.c for zappy in server
**
** Made by Edouard
** Login   <edouard@epitech.net>
**
** Started on  Tue Jun 27 17:33:50 2017 Edouard
** Last update Sun Jul  2 19:09:41 2017 Edouard
*/

#include <string.h>
#include <server/gui_events.h>
#include "server.h"

int	ia_death(t_server *server, ID id, char *cmd)
{
  (void) cmd;
  event_pdi(server, id);
  strncircular(&server->game.clients[id].w, "death\n", strlen("death\n"));
  return (0);
}

/*
** gui_pin.c for zappy in server/src/id_commands
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sun Jun 25 02:18:24 2017 brout_m
** Last update Sun Jul  2 15:44:01 2017 Edouard
*/

#include <string.h>
#include <stdlib.h>
#include "server.h"

int	send_player_inventory(t_server *server, ID id)
{
  int	i;
  t_ia	*ia;

  i = 0;
  ia = &server->game.clients[id].ia;
  send_to_gui(server, "pin %d %d %d ", id, ia->pos.x, ia->pos.y);
  while (i < OBJ_COUNT)
    {
      send_to_gui(server, "%d", ia->inventory[i]);
      if (i < OBJ_COUNT - 1)
	send_to_gui(server, " ");
      ++i;
    }
  return (send_to_gui(server, "\nplv %d %d\n", id, ia->level));
}

int	gui_pin(t_server *server, ID ids, char *cmd)
{
  char	*idstr;
  int	id;

  (void)ids;
  strtok(cmd, " ");
  if ((idstr = strtok(NULL, " ")) == NULL)
    return (send_to_gui(server, "suc\n"));
  id = atoi(idstr);
  if (find_ID(server, id, true) < 0)
    return (send_to_gui(server, "sbp\n"));
  log_this("[PIN] GUI asked for Client '%d' inventory\n", id);
  return (send_player_inventory(server, id));
}

/*
** event_pbc.c for zappy in server/src/gui_events
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sun Jun 25 02:28:01 2017 brout_m
** Last update Sun Jul  2 15:50:29 2017 Edouard
*/

#include "server.h"

int	event_pbc(t_server *server, ID id, char const *broadcast)
{
  log_this("[PBC] Client '%d' Broadcasting : %s\n", id, broadcast);
  return (send_to_gui(server, "pbc %d %s\n", id, broadcast));
}

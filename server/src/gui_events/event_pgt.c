/*
** event_pgt.c for zappy in server/src/gui_events
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sun Jun 25 02:30:13 2017 brout_m
** Last update Sun Jul  2 15:51:42 2017 Edouard
*/

#include "server.h"

int	event_pgt(t_server *server, ID id, enum e_object obj)
{
  log_this("[PGT] Client '%d' take object %s\n", id, nameof(obj));
  return (send_to_gui(server, "pgt %d %d\n", id, obj));
}

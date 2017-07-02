/*
** event_pdr.c for zappy in server/src/gui_events
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sun Jun 25 02:28:42 2017 brout_m
** Last update Sun Jul  2 15:50:50 2017 Edouard
*/

#include "server.h"

int	event_pdr(t_server *server, ID id, enum e_object obj)
{
  log_this("[PDR] Client '%d' threw %s\n", id, nameof(obj));
  return (send_to_gui(server, "pdr %d %d\n", id, obj));
}

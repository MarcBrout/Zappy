/*
** event_pdi.c for zappy in server/src/gui_events
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sun Jun 25 02:28:15 2017 brout_m
** Last update Sun Jul  2 15:50:54 2017 Edouard
*/

#include "server.h"

int	event_pdi(t_server *server, ID id)
{
  log_this("[PDI] Client '%d' starved\n", id);
  return (send_to_gui(server, "pdi %d\n", id));
}

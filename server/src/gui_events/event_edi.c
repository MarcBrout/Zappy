/*
** event_edi.c for zappy in server/src/gui_events
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sun Jun 25 02:26:31 2017 brout_m
** Last update Sun Jul  2 15:49:34 2017 Edouard
*/

#include "server.h"

int	event_edi(t_server *server, ID id)
{
  log_this("[EDI] Egg '%d' starved to death\n", id);
  return (send_to_gui(server, "edi %d\n", id));
}

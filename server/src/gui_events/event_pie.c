/*
** event_pie.c for zappy in server/src/gui_events
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sun Jun 25 02:31:11 2017 brout_m
** Last update Sun Jun 25 02:31:34 2017 brout_m
*/
#include "server.h"

int event_pie(t_server *server, t_position const *pos, int result)
{
  log_this("[PEX] Incantation %s on:\n\tx: %d\n\ty: %d\n",
	   (result ? "SUCCEEDED" : "FAILED"), pos->x, pos->y);
  return (send_to_gui(server, "pie %d %d %d\n", pos->x, pos->y, result));
}

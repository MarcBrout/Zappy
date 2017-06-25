/*
** event_pex.c for zappy in server/src/gui_events
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sun Jun 25 02:29:06 2017 brout_m
** Last update Sun Jun 25 02:29:29 2017 brout_m
*/
#include "server.h"

int event_pex(t_server *server, ID id)
{
  log_this("[PEX] Client '%d' ejecting\n", id);
  return (send_to_gui(server, "pex %d\n", id));
}

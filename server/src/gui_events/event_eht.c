/*
** event_eht.c for zappy in server/src/gui_events
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sun Jun 25 02:26:50 2017 brout_m
** Last update Sun Jul  2 15:49:45 2017 Edouard
*/

#include "server.h"

int	event_eht(t_server *server, ID id)
{
  log_this("[EHT] Egg '%d' Hatched\n", id);
  return (send_to_gui(server, "eht %d\n", id));
}

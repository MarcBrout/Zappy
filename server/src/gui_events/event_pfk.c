/*
** event_pfk.c for zappy in server/src/gui_events
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sun Jun 25 02:29:50 2017 brout_m
** Last update Sun Jul  2 15:51:33 2017 Edouard
*/

#include "server.h"

int event_pfk(t_server *server, ID id)
{
  log_this("[PFK] Client '%d' layed and egg\n", id);
  return (send_to_gui(server, "pfk %d\n", id));
}

/*
** event_seg.c for zappy in server/src/gui_events
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sun Jun 25 02:32:17 2017 brout_m
** Last update Sun Jul  2 15:54:09 2017 Edouard
*/

#include "server.h"

int	event_seg(t_server *server, char const *winner)
{
  log_this("[SEG] GAME OVER! WINNER %s\n", winner);
  return (send_to_gui(server, "seg %s\n", winner));
}

/*
** event_ebo.c for zapyy in server/src/gui_events
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sun Jun 25 02:26:09 2017 brout_m
** Last update Sun Jul  2 15:49:13 2017 Edouard
*/

#include "server.h"

int	event_ebo(t_server *server, ID eggId)
{
  log_this("[EBO] Client connected on egg '%d'\n", eggId);
  return (send_to_gui(server, "ebo %d\n", eggId));
}

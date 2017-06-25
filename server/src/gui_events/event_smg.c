/*
** event_smg.c for zappy in server/src/gui_events
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sun Jun 25 02:32:36 2017 brout_m
** Last update Sun Jun 25 02:32:52 2017 brout_m
*/
#include "server.h"

int event_smg(t_server *server, char const *smg)
{
  log_this("[SMG] Server message %s\n", smg);
  return (send_to_gui(server, "smg %s\n", smg));
}

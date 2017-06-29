/*
** event_pnw.c for zappy in server/src/gui_events
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sun Jun 25 02:31:43 2017 brout_m
** Last update Wed Jun 28 10:43:03 2017 brout_m
*/
#include "server.h"

int event_pnw(t_server *server, t_client const *newClient)
{
  log_this("[PNW] New client '%d' of team '%s' and level '%d'"
	   ", facing '%d', connected on:\n\tx: %d\n\ty: %d",
	   newClient->id, server->config.teams[newClient->ia.team].name,
	   newClient->ia.level, newClient->ia.dir, newClient->ia.pos.x,
	   newClient->ia.pos.y);
  return (send_to_gui(server, "pnw %d %d %d %d %d %s\n", newClient->id,
		      newClient->ia.pos.x, newClient->ia.pos.y,
		      newClient->ia.dir, newClient->ia.level,
		      server->config.teams[newClient->ia.team]));
}

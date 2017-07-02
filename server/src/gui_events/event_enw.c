/*
** event_enw.c for zappy in server/src/gui_events
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sun Jun 25 02:27:41 2017 brout_m
** Last update Sun Jul  2 15:50:03 2017 Edouard
*/

#include "server.h"

int	event_enw(t_server *server, ID id, t_egg const *egg)
{
  log_this("[ENW] Client '%d' layed egg '%d' on:\n\tx : %d\n\ty : %d\n",
	   id, egg->id, egg->pos.x, egg->pos.y);
  return (send_to_gui(server, "enw %d %d %d %d\n", egg->id, id, egg->pos.x,
		      egg->pos.y));
}

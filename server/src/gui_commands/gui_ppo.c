/*
** gui_ppo.c for zappy in server/src/id_commands
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sun Jun 25 02:19:55 2017 brout_m
** Last update Sun Jun 25 02:22:49 2017 brout_m
*/
#include <string.h>
#include <stdlib.h>
#include "server.h"

int		send_player_position(t_server *server, ID id)
{
  t_ia		*ia;

  ia = &server->game.clients[id].ia;
  log_this("[PPO] GUI asked for Client '%d' position on:"
	   "\n\tx: %d\n\ty: %d\n\tdir: %d\n ", id,
           ia->pos.x, ia->pos.y, ia->dir);
  return (send_to_gui(server, "ppo #%d %d %d %d\n",
                      id, ia->pos.x, ia->pos.y, ia->dir));
}

int		gui_ppo(t_server *server, ID ids, char *cmd)
{
  char		*idstr;
  int		id;

  (void)ids;
  strtok(cmd, " ");
  if ((idstr = strtok(NULL, " ")) == NULL)
    return (send_to_gui(server, "suc\n"));
  if (idstr[0] != '#')
    return (send_to_gui(server, "sbp\n"));
  id = atoi(idstr);
  if (find_ID(server, id, true) < 0)
    return (send_to_gui(server, "sbp\n"));
  return (send_player_position(server, id));
}

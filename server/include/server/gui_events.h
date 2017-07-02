/*
** gui_events.h for zappy in /home/rendu/system/PSU_2016_zappy
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sat Jun 24 16:42:54 2017 brout_m
** Last update Sun Jul  2 18:53:59 2017 Edouard
*/
#ifndef GUI_EVENTS_H_
# define GUI_EVENTS_H_

# include "server.h"

int event_ebo(t_server *server, ID eggId);
int event_edi(t_server *server, ID eggId);
int event_eht(t_server *server, ID eggId);
int event_enw(t_server *server, ID clientId, t_egg const *egg);
int event_pbc(t_server *server, ID clientId, char const *broadcast);
int event_pdi(t_server *server, ID clientId);
int event_pdr(t_server *server, ID clientId, enum e_object obj);
int event_pex(t_server *server, ID clientId);
int event_pfk(t_server *server, ID clientId);
int event_pgt(t_server *server, ID clientId, enum e_object obj);
int event_pic(t_server *server, t_client const *client);
int event_pie(t_server *server, t_position const *pos, int incantationResult);
int event_pnw(t_server *server, t_client const *newClient);
int event_seg(t_server *server, char const *winnerTeamName);
int event_smg(t_server *server, char const *serverMessage);

#endif /* !GUI_EVENTS_H_ */

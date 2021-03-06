/*
** ia_commands.h for zappy in server/include/server
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sat Jun 24 16:43:42 2017 brout_m
** Last update Sun Jul  2 14:27:51 2017 Edouard
*/

#ifndef IA_COMMANDS_H_
# define IA_COMMANDS_H_

# include "server_data.h"

# define MAX_INCANT 7

int	ia_unknown(t_server *server, ID id, char *cmd);
int	ia_forward(t_server *server, ID id, char *cmd);
int	ia_right(t_server *server, Socket id, char *cmd);
int	ia_left(t_server *server, Socket id, char *cmd);
int	ia_look(t_server *server, ID id, char *cmd);
int	ia_inventory(t_server *server, ID id, char *cmd);
int	ia_broadcast(t_server *server, ID id, char *cmd);
int	ia_connect_nbr(t_server *server, ID id, char *cmd);
int	ia_fork(t_server *server, ID id, char *cmd);
int	ia_eject(t_server *server, ID id, char *cmd);
int	ia_take(t_server *server, ID id, char *cmd);
int	ia_set(t_server *server, ID id, char *cmd);
int	ia_incantation(t_server *server, ID id, char *cmd);
int	ia_death(t_server *server, ID id, char *cmd);
bool	is_incantation(t_server *server, t_position *pos);
int	push_value(t_server *server, Object type, bool start);

#endif /* !IA_COMMANDS_H_ */

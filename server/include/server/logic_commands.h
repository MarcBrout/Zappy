/*
** logic_commands.h for zappy in server/include/server
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sat Jun 24 16:44:11 2017 brout_m
** Last update Sat Jun 24 16:44:28 2017 brout_m
*/
#ifndef LOGIC_COMMANDS_H_
# define LOGIC_COMMANDS_H_

int 	logic_unknown(t_server *server, ID id, char *cmd);
int 	logic_forward(t_server *server, ID id, char *cmd);
int	logic_right(t_server *server, Socket id, char *cmd);
int 	logic_left(t_server *server, Socket id, char *cmd);
int 	logic_look(t_server *server, ID id, char *cmd);
int 	logic_inventory(t_server *server, ID id, char *cmd);
int 	logic_broadcast(t_server *server, ID id, char *cmd);
int 	logic_connect_nbr(t_server *server, ID id, char *cmd);
int 	logic_fork(t_server *server, ID id, char *cmd);
int 	logic_eject(t_server *server, ID id, char *cmd);
int 	logic_take(t_server *server, ID id, char *cmd);
int 	logic_set(t_server *server, ID id, char *cmd);
int	logic_incantation(t_server *server, ID id, char *cmd);
int	logic_fork_start(t_server *server, ID id, char *cmd);
int	logic_incantation_start(t_server *server, ID id, char *cmd);
void	forward_pos(t_server *server, t_position *pos, Direction dir, int nb);

#endif /* !LOGIC_COMMANDS_H_ */

//
// Created by brout_m on 09/06/17.
//

#ifndef IA_COMMANDS_H_
#define IA_COMMANDS_H_

# include "server_data.h"

int ia_unknown(t_server *server, Socket sock, char *cmd);
int ia_forward(t_server *server, Socket sock, char *cmd);
int ia_right(t_server *server, Socket sock, char *cmd);
int ia_left(t_server *server, Socket sock, char *cmd);
int ia_look(t_server *server, Socket sock, char *cmd);
int ia_inventory(t_server *server, Socket sock, char *cmd);
int ia_broadcast(t_server *server, Socket sock, char *cmd);
int ia_connect_nbr(t_server *server, Socket sock, char *cmd);
int ia_fork(t_server *server, Socket sock, char *cmd);
int ia_eject(t_server *server, Socket sock, char *cmd);
int ia_take(t_server *server, Socket sock, char *cmd);
int ia_set(t_server *server, Socket sock, char *cmd);
int ia_incantation(t_server *server, Socket sock, char *cmd);
void move_to_dir(t_server *server, t_client *client, Direction dir);

#endif //IA_COMMANDS_H_

/*
** gui_commands.h for zappy in server/include/server
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sat Jun 24 16:42:26 2017 brout_m
** Last update Sat Jun 24 16:42:48 2017 brout_m
*/
#ifndef GUI_COMMANDS_H_
# define GUI_COMMANDS_H_

# include "server_data.h"

int send_case_content(t_server *server, int x, int y);
int gui_unknown(t_server *server, ID id, char *cmd);
int gui_welcome(t_server *server, ID id, char *cmd);
int gui_msz(t_server *server, ID id, char *cmd);
int gui_bct(t_server *server, ID id, char *cmd);
int gui_mct(t_server *server, ID id, char *cmd);
int gui_tna(t_server *server, ID id, char *cmd);
int gui_ppo(t_server *server, ID id, char *cmd);
int gui_plv(t_server *server, ID id, char *cmd);
int gui_pin(t_server *server, ID id, char *cmd);
int gui_sgt(t_server *server, ID id, char *cmd);
int gui_sst(t_server *server, ID id, char *cmd);
bool set_gui_connected(bool value, bool set);
int send_player_position(t_server *server, ID id);
int send_player_inventory(t_server *server, ID id);
int send_player_lvl(t_server *server, ID id);
int send_informations(t_server *server);

#endif /* !GUI_COMMANDS_H_ */

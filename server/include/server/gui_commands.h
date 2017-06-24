//
// Created by brout_m on 09/06/17.
//

#ifndef GUI_COMMANDS_H_
#define GUI_COMMANDS_H_

#include "server_data.h"

int send_case_content(t_server *server, int x, int y);
int gui_unknown(t_server *server, ID id, char *cmd);
int gui_msz(t_server *server, ID id, char *cmd);
int gui_bct(t_server *server, ID id, char *cmd);
int gui_mct(t_server *server, ID id, char *cmd);
int gui_tna(t_server *server, ID id, char *cmd);
int gui_ppo(t_server *server, ID id, char *cmd);
int gui_plv(t_server *server, ID id, char *cmd);
int gui_pin(t_server *server, ID id, char *cmd);
int gui_sgt(t_server *server, ID id, char *cmd);
int gui_sst(t_server *server, ID id, char *cmd);

#endif /* !GUI_COMMANDS_H_ */

//
// Created by brout_m on 09/06/17.
//

#ifndef SEND_H_
#define SEND_H_

#include "server_data.h"

int send_to_gui(t_server *server, char const *fmt, ...);
int send_to_ia(t_server *server, Socket sock, char const *fmt, ...);

#endif //SEND_H_

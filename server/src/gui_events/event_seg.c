//
// Created by brout_m on 23/06/17.
//

#include "server.h"

int event_seg(t_server *server, char const *winner)
{
  return (send_to_gui(server, "seg %s\n", winner));
}
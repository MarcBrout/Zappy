//
// Created by brout_m on 09/06/17.
//

#include "server.h"

int ia_unknown(t_server *server, ID id, char *cmd)
{
  (void)cmd;
  send_to_ia(server, id, "ko\n");
  return (0);
}

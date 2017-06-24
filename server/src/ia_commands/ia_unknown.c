//
// Created by brout_m on 09/06/17.
//

#include "server.h"

int ia_unknown(t_server *server, t_client *client, char *cmd)
{
  (void)cmd;
  send_to_ia(server, client->sock, "ko\n");
  return (0);
}

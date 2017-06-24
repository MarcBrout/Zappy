//
// Created by brout_m on 24/06/17.
//

#include "server.h"

int logic_unknown(t_server *server, t_client *client, char *cmd)
{
  (void)cmd;
  send_to_ia(server, client->sock, "ko\n");
  return (0);
}
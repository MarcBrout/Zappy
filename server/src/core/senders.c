//
// Created by brout_m on 09/06/17.
//

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "server/server_data.h"

int send_to_gui(t_server *server, char const *fmt, ...)
{
  char cmd[MESSAGE_MAX_SIZE];
  va_list va;

  va_start(va, fmt);
  memset(cmd, 0, MESSAGE_MAX_SIZE);
  if (vsnprintf(cmd, MESSAGE_MAX_SIZE, fmt, va) < 0)
    return (1);
  va_end(va);
  strncircular(&server->gui.w, cmd, (int)strlen(cmd));
  return (0);
}

int send_to_ia(t_server *server, Socket sock, char const *fmt, ...)
{
  char cmd[MESSAGE_MAX_SIZE];
  va_list va;

  va_start(va, fmt);
  memset(cmd, 0, MESSAGE_MAX_SIZE);
  if (vsnprintf(cmd, MESSAGE_MAX_SIZE, fmt, va) < 0)
    return (1);
  va_end(va);
  strncircular(&server->game.clients[sock].w, cmd, (int)strlen(cmd));
  return (0);
}
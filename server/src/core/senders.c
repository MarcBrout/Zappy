/*
** senders.c for zappy in server/src/core
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sun Jun 25 02:49:14 2017 brout_m
** Last update Sun Jun 25 02:49:24 2017 brout_m
*/
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "server/server_data.h"

int		send_to_gui(t_server *server, char const *fmt, ...)
{
  char		cmd[MESSAGE_MAX_SIZE];
  va_list	va;

  va_start(va, fmt);
  memset(cmd, 0, MESSAGE_MAX_SIZE);
  if (vsnprintf(cmd, MESSAGE_MAX_SIZE, fmt, va) < 0)
    return (1);
  va_end(va);
  strncircular(&server->gui.w, cmd, (int)strlen(cmd));
  return (0);
}

int		send_to_ia(t_server *server, ID id, char const *fmt, ...)
{
  char		cmd[MESSAGE_MAX_SIZE];
  va_list	va;

  va_start(va, fmt);
  memset(cmd, 0, MESSAGE_MAX_SIZE);
  if (vsnprintf(cmd, MESSAGE_MAX_SIZE, fmt, va) < 0)
    return (1);
  va_end(va);
  strncircular(&server->game.clients[id].w, cmd, (int)strlen(cmd));
  return (0);
}

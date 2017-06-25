/*
** logic_unknown.c for zappy in server/src/ia_logic
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sun Jun 25 03:09:56 2017 brout_m
** Last update Sun Jun 25 03:10:14 2017 brout_m
*/
#include "server.h"

int logic_unknown(t_server *server, ID id, char *cmd)
{
  (void)cmd;
  send_to_ia(server, id, "ko\n");
  return (0);
}

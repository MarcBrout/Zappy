/*
** help.c for zappy in server/src
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sat Jun 24 17:02:06 2017 brout_m
** Last update Sun Jul  2 15:27:17 2017 Edouard
*/
#include <stdio.h>

static const char	*usage =
  "USAGE: %s -p port -x width -y height -n name1 name2 -c nbClients -f time\n"
  "\tport\t\tis the port number\t\t\t\tdefault : 4242\n"
  "\twidth\t\tis the width of the world\t\t\tdefault : 30\n"
  "\theight\t\tis the height of the world\t\t\tdefault : 30\n"
  "\tnameX\t\tis the name of the team X\t\t\tmandatory\n"
  "\tclients Nb\tis the number of authorized clients per team\tdefault : 10\n"
  "\tfreq\t\tis the time limit for execution of actions\tdefault : 100\n";

int	print_help(char *server_name)
{
  return (printf(usage, server_name) || 1);
}

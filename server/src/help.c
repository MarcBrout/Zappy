#include <stdio.h>

static const char *usage =
"USAGE: %s -p port -x width -y height -n name1 name2 -c nbClients -t time\n"
    "\tport\t\tis the port number\n"
    "\twidth\t\tis the width of the world\n"
    "\theight\t\tis the height of the world\n"
    "\tname1\t\tis the name of the team 1\n"
    "\tname2\t\tis the name of the team 2\n"
    "\tnbClients\tis the number of authorized clients per team\n"
    "\ttime\t\tis the time limit for execution of actions\n";

int print_help(char *server_name)
{
  return (printf(usage, server_name) || 1);
}
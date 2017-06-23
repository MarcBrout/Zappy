#include <stdlib.h>
#include <string.h>
#include "server.h"
#include "argument_processor.h"

int main(int ac, char **av)
{
  t_server server;

  memset(&server, 0, sizeof(server));
  log_this("Server started, parsing arguments...\n");
  if (process_command_line(&server.config, ac, av) ||
      launch_server(&server))
    return (84);
  return (EXIT_SUCCESS);
}
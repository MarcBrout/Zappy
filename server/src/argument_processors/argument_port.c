#include <stdio.h>
#include <stdlib.h>
#include "arguments/config.h"

int argument_port(t_config *config, int ac, char **argv, int *pos)
{
  int port;

  if (*pos > ac - 2)
    return (1);
  ++*pos;
  port = atoi(argv[*pos]);
  if (port <= 1024 || port > 65536)
  {
    printf("Port '%d' incorrect, value must be between 1024 && 65536\n", port);
    return (1);
  }
  config->port = (uint16_t)port;
  return (0);
}
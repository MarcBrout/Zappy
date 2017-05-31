#include <config.h>
#include <stdlib.h>

int argument_port(t_config *config, char **argv, int *pos)
{
  int port;

  ++*pos;
  port = atoi(argv[*pos]);
  if (port <= 1024 || port > 65536)
    return (1);
  config->port = (uint16_t)port;
  return (0);
}
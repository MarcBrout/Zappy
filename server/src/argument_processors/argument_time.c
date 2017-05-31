#include <stdlib.h>
#include "types.h"

int argument_time(t_config *config, char **argv, int *pos)
{
  int time;

  ++*pos;
  time = atoi(argv[*pos]);
  if (time < 2 || time >= MAX_HEIGHT)
    return (1);
  config->time = (uint8_t)time;
  return (0);
}
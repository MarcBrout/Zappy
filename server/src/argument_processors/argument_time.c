#include <stdlib.h>
#include <stdio.h>
#include "arguments/config.h"

int argument_time(t_config *config, int ac, char **argv, int *pos)
{
  int time;

  if (*pos > ac - 2)
    return (1);
  ++*pos;
  time = atoi(argv[*pos]);
  if (time < 1 || time >= MAX_TIME)
  {
    printf("Time value incorrect, value must be between 1 && %d\n",
           MAX_TIME);
    return (1);
  }
  config->time = (uint16_t)time;
  return (0);
}
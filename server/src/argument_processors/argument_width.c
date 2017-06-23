#include <stdio.h>
#include <stdlib.h>
#include "arguments/config.h"

int argument_width(t_config *config, int ac, char **argv, int *pos)
{
  int width;

  if (*pos > ac - 2)
    return (1);
  ++*pos;
  width = atoi(argv[*pos]);
  if (width < 2 || width >= MAX_WIDTH)
  {
    printf("Width value incorrect, value must be between 1 && %d\n",
    MAX_WIDTH);
    return (1);
  }
  config->width = (uint8_t)width;
  return (0);
}
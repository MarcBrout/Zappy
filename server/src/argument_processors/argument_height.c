#include <stdlib.h>
#include "arguments/config.h"

int argument_height(t_config *config, int ac, char **argv, int *pos)
{
  int height;

  if (*pos > ac - 2)
    return (1);
  ++*pos;
  height = atoi(argv[*pos]);
  if (height < 2 || height >= MAX_HEIGHT)
    return (1);
  config->height = (uint8_t)height;
  return (0);
}
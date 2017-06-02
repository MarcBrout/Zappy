#include <stdlib.h>
#include "arguments/config.h"

int argument_height(t_config *config, char **argv, int *pos)
{
  int height;

  ++*pos;
  height = atoi(argv[*pos]);
  if (height < 2 || height >= MAX_HEIGHT)
    return (1);
  config->height = (uint8_t)height;
  return (0);
}
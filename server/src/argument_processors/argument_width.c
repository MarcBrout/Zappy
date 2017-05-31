#include <stdlib.h>
#include "types.h"

int argument_width(t_config *config, char **argv, int *pos)
{
  int width;

  ++*pos;
  width = atoi(argv[*pos]);
  if (width < 2 || width >= MAX_WIDTH)
    return (1);
  config->width = (uint8_t)width;
  return (0);
}
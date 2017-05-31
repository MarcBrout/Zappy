#include <stdlib.h>
#include "types.h"

int argument_nbclients(t_config *config, char **argv, int *pos)
{
  int nbclients;

  ++*pos;
  nbclients = atoi(argv[*pos]);
  if (nbclients < 2 || nbclients >= MAX_CLIENT)
    return (1);
  config->max_player = (uint8_t)nbclients;
  return (0);
}

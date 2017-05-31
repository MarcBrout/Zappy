#include <string.h>
#include "types.h"

int argument_name(t_config *config, char **argv, int *pos)
{
  ++*pos;
  if ((config->team1 = strdup(argv[*pos])) == NULL)
    return (1);
  ++*pos;
  if ((config->team2 = strdup(argv[*pos])) == NULL)
    return (1);
  return (0);
}

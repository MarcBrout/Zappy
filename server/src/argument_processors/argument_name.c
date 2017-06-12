#include "arguments/config.h"
#include <string.h>

int argument_name(t_config *config, int ac, char **argv, int *pos)
{
  if (*pos > ac - 3 || argv[*pos + 1][0] == '-' || argv[*pos + 2][0] == '-')
      return (1);
  ++*pos;
  if ((config->team1 = strdup(argv[*pos])) == NULL)
    return (1);
  ++*pos;
  if ((config->team2 = strdup(argv[*pos])) == NULL)
    return (1);
  return (0);
}
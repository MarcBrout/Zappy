#include <stdlib.h>
#include "arguments.h"
#include "types.h"

int main(int ac, char **av)
{
  t_config config = {};

  if (process_command_line(&config, ac, av))
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}
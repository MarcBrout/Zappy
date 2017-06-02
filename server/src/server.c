#include <stdlib.h>
#include "arguments/arguments.h"
#include "arguments/config.h"

int main(int ac, char **av)
{
  t_config config;

  if (process_command_line(&config, ac, av))
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}
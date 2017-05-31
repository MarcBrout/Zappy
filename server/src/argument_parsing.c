#include <stdlib.h>
#include <string.h>
#include "arguments.h"
#include "config.h"

static const t_arg commands[7] =
    {
        { "-p", argument_port },
        { "-x", argument_width },
        { "-y", argument_height },
        { "-n", argument_name },
        { "-c", argument_nbclients },
        { "-t", argument_time },
        { NULL, NULL }
    };

int process_command_line(t_config *config, int ac, char **args)
{
  int argument;
  int i;

  if (ac < 14)
    return (print_help(args[0]) || EXIT_FAILURE);
  argument = 1;
  while (argument < ac - 1)
  {
    i = 0;
    while (commands[i].cmd != NULL)
    {
      if (!strcmp(commands[i].cmd, args[argument]))
      {
        if (commands[i].exec(config, args, &argument))
          return (print_help(args[0]) || EXIT_FAILURE);
        break;
      }
      ++i;
    }
    if (commands[i].cmd == NULL)
      return (print_help(args[0]) || EXIT_FAILURE);
    ++argument;
  }
  return (0);
}
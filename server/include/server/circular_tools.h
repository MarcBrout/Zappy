/*
** circular_tools.h for myirc in /home/brout_m/rendu/system/PSU_2016_myirc
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Wed May 31 11:11:52 2017 brout_m
** Last update Wed May 31 11:13:50 2017 brout_m
*/

#ifndef CIRCULAR_TOOLS_H_
# define CIRCULAR_TOOLS_H_

# include <stdbool.h>

# define MESSAGE_MAX_SIZE 4096
# define BUFFER_MAX_SIZE 4096
# define INCR(x) ((x) = ((x) + 1) % BUFFER_MAX_SIZE)

typedef struct		s_circular t_circular;

struct			s_circular
{
  int			pos;
  int			len;
  char			buffer[BUFFER_MAX_SIZE];
};

void strncircular(t_circular *read_cir, char *str, int n);
bool find_command(t_circular *cir);
bool strfromcircular(t_circular *cir, char out[MESSAGE_MAX_SIZE]);

#endif /* !MYIRC_CIRCULAR_TOOLS_H_ */

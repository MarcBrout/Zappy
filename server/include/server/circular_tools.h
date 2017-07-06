/*
** circular_tools.h for zappy in server/include/server
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sat Jun 24 16:40:57 2017 brout_m
** Last update Thu Jul  6 16:22:09 2017 brout_m
*/

#ifndef CIRCULAR_TOOLS_H_
# define CIRCULAR_TOOLS_H_

# include <stdbool.h>

# define MESSAGE_MAX_SIZE 16384
# define BUFFER_MAX_SIZE 16384
# define INCR(x) ((x) = ((x) + 1) % BUFFER_MAX_SIZE)

typedef struct		s_circular t_circular;

struct	s_circular
{
  bool	remains;
  int	pos;
  int	len;
  char	buffer[BUFFER_MAX_SIZE];
};

void	strncircular(t_circular *read_cir, char *str, int n);
bool	find_command(t_circular *cir);
bool	strfromcircular(t_circular *cir, char out[MESSAGE_MAX_SIZE]);
void	resetBuffer(t_circular *c);

#endif /* !CIRCULAR_TOOLS_H_ */

/*
** timer.h for zappy in server/include/timer
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sat Jun 24 16:53:20 2017 brout_m
** Last update Sat Jun 24 16:53:56 2017 brout_m
*/
#ifndef TIMER_H_
# define TIMER_H_

# include <stdbool.h>
# include <stdint.h>
# include <sys/time.h>

typedef struct s_timer	Timer;

struct			s_timer
{
  struct timeval	start;
  struct timeval	now;
  uint64_t		freq;
  uint64_t		new_freq;
};

int init_timer(uint16_t freq);
bool isTick();
void set_new_timer(uint16_t freq);

#endif /* !TIMER_H_ */

/*
** timer.c for zappy in server/src/timer
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sun Jun 25 03:07:02 2017 brout_m
** Last update Sun Jul  2 15:55:58 2017 Edouard
*/

#include <string.h>
#include <stdio.h>
#include <time.h>
#include "logger.h"
#include "timer.h"

static Timer		timer;
static suseconds_t	last = 0;

int		init_timer(uint16_t freq)
{
  double	unit = 1.0;

  memset(&timer, 0, sizeof(timer));
  if (gettimeofday(&timer.start, NULL))
    {
      perror("Timer initialization");
      return (1);
    }
  timer.freq = (uint64_t)((unit / (double)freq) * 1000000.0);
  timer.new_freq = timer.freq;
  log_this("Timer correctly set at : \n\tstart: %s\tfreq: %u\n",
	   ctime(&timer.start.tv_sec), timer.freq);
  return (0);
}

void	set_new_timer(uint16_t freq)
{
  timer.new_freq = (uint64_t)((1.0 / (double)freq) * 1000000.0);
}

bool		isTick()
{
  suseconds_t	diff;

  gettimeofday(&timer.now, NULL);
  diff = ((1000000ll * timer.now.tv_sec + timer.now.tv_usec) -
	  (1000000ll * timer.start.tv_sec + timer.start.tv_usec)) /
    timer.freq;
  if (diff > last)
    {
      if (timer.new_freq != timer.freq)
	timer.freq = timer.new_freq;
      log_this("\t======= TICK REACHED =======\n");
      last = diff;
      return (true);
    }
  return (false);
}

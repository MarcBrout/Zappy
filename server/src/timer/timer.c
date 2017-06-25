/*
** timer.c for zappy in server/src/timer
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sun Jun 25 03:07:02 2017 brout_m
** Last update Sun Jun 25 03:07:13 2017 brout_m
*/
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "logger.h"
#include "timer.h"

static Timer	timer;

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
  log_this("Timer correctly set at : \n\tstart: %s\tfreq: %u\n",
           ctime(&timer.start.tv_sec), timer.freq);
  return (0);
}

bool		isTick()
{
  suseconds_t	diff;

  gettimeofday(&timer.now, NULL);
  diff = timer.now.tv_usec - timer.start.tv_usec;
  if ((diff % timer.freq) <= 10)
    {
      log_this("\t======= TICK REACHED =======\n");
      return (true);
    }
  return (false);
}

//
// Created by brout_m on 24/06/17.
//

#include <string.h>
#include <stdio.h>
#include <time.h>
#include "logger.h"
#include "timer.h"

static Timer timer;

int init_timer(uint16_t freq)
{
  double unit = 1.0;

  memset(&timer, 0, sizeof(timer));
  if (gettimeofday(&timer.start, NULL))
  {
    perror("Timer initialization");
    return (1);
  }
  timer.freq = (uint64_t)((unit / (double)freq) * 1000000.0);
  log_this("Timer correctly set at : \n\tstart: %s\n\tfreq: %u\n",
           ctime(&timer.start.tv_sec), timer.freq);
  return (0);
}

bool isTick()
{
  suseconds_t diff;

  gettimeofday(&timer.now, NULL);
  diff = timer.now.tv_usec - timer.start.tv_usec;
  if (!(diff % timer.freq))
  {
    log_this("\t======= TICK REACHED =======\n");
    return (true);
  }
  return (false);
}
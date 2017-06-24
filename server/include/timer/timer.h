//
// Created by brout_m on 24/06/17.
//

#ifndef TIMER_H_
#define TIMER_H_

#include <stdbool.h>
#include <stdint.h>
#include <sys/time.h>

typedef struct s_timer Timer;

struct s_timer
{
  struct timeval start;
  struct timeval now;
  uint64_t freq;
};

int init_timer(uint16_t freq);
bool isTick();

#endif /* !TIMER_H_ */

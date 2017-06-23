//
// Created by brout_m on 23/06/17.
//
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void log_this(char const *fmt, ...)
{
  #ifdef DEBUG
  va_list ap;

  va_start(ap, fmt);
  if (vfprintf(stdout, fmt, ap) == -1)
    exit(84);
  va_end(ap);
  #else
  (void)fmt;
  #endif
}
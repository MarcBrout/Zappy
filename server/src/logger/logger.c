/*
** logger.c for zappy in server/src/logger
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sun Jun 25 03:05:27 2017 brout_m
** Last update Sun Jun 25 03:05:33 2017 brout_m
*/
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void		log_this(char const *fmt, ...)
{
#ifdef DEBUG
  va_list	ap;

  va_start(ap, fmt);
  if (vfprintf(stdout, fmt, ap) == -1)
    exit(84);
  va_end(ap);
#else
  (void)fmt;
#endif
}

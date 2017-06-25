/*
** internationalization.c for zappy in server/src/core
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sun Jun 25 02:39:07 2017 brout_m
** Last update Sun Jun 25 02:39:16 2017 brout_m
*/
#include "server/server_types.h"

static char const	*names[OBJ_COUNT] =
  {
    "food",
    "linemate",
    "deraumere",
    "sibur",
    "mendiane",
    "phiras",
    "thystame"
  };

inline const char	*nameof(enum e_object obj)
{
  return (obj > THYSTAME ? "unknown object" : names[obj]);
}

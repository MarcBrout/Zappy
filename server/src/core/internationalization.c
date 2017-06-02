//
// Created by brout_m on 02/06/17.
//

#include "server/server_types.h"

static char const *names[THYSTAME] =
    {
        "food",
        "linemate",
        "deraumere",
        "sibur",
        "mendiane",
        "phiras",
        "thystame"
    };

static char const *none = "none";

inline const char *nameof(enum e_object obj)
{
  return (obj > THYSTAME ? none : names[obj]);
}
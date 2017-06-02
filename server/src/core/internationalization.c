//
// Created by brout_m on 02/06/17.
//

#include "server/server_types.h"

static char const *names[OBJ_COUNT] =
    {
        "food",
        "linemate",
        "deraumere",
        "sibur",
        "mendiane",
        "phiras",
        "thystame",
        "none"
    };

inline const char *nameof(enum e_object obj)
{
  return (obj > THYSTAME ? names[OBJ_COUNT] : names[obj]);
}
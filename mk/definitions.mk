#######################################################
### Some basic C++ definitions for arcade Makefiles ###
#######################################################

# MODE

DEBUG	=	NO

RELEASE	=	NO

DLL	=	NO

SANITIZE =	NO

# NAME

PROJECT_NAME	=

# Compilation definitions

CFLAGS		=	-W -Wall -Wextra

ifeq ($(RELEASE), YES)
CFLAGS		+=	-Werror
else
ifeq ($(DEBUG), YES)
CFLAGS		+=	-D DEBUG -g
endif
endif

ifeq ($(DLL), YES)
CFLAGS	+=	-fPIC -ldl
endif
ifeq ($(STATIC), YES)
CFLAGS	+=	-fPIC
endif

ifeq ($(SANITIZE), YES)
CFLAGS	+=	-fsanitize=memory -fsanitize-memory-track-origins=2 -fomit-frame-pointer
endif

CC	=	gcc

LDFLAGS	=

ifeq ($(DLL), YES)
CC	+= -shared
endif

ifeq ($(STATIC), YES)
LINKER = ar -rcs
endif

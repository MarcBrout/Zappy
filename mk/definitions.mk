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

ifeq ($(RELEASE),yes)
CFLAGS		+=	-Werror
else
ifeq ($(DEBUG),yes)
CFLAGS		+=	-D DEBUG -g
endif
endif

ifeq ($(DLL),yes)
CFLAGS	+=	-fPIC -ldl
endif
ifeq ($(STATIC),yes)
CFLAGS	+=	-fPIC
endif

ifeq ($(SANITIZE),yes)
CFLAGS	+=	-fsanitize=memory -fsanitize-memory-track-origins=2 -fomit-frame-pointer
endif

CC	=	gcc

LDFLAGS	=

ifeq ($(DLL),yes)
CC	+= -shared
endif

ifeq ($(STATIC),yes)
LINKER = ar -rcs
endif

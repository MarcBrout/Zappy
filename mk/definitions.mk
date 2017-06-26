########################################################
###    Some basic C/C++ definitions for Makefiles    ###
########################################################

##### MODE #####

DEBUG	=	NO

RELEASE	=	NO

DLL	=	NO

SANITIZE =	NO

MODE	=	CPP

##### NAME #####

PROJECT_NAME	=

##### Compilation definitions #####

CFLAGS		=	-W -Wall -Wextra
CXXFLAGS	=	-W -Wall -Wextra -Weffc++ -std=c++14 -Wcomment          \
                -Wmain -Wpointer-arith -Wreturn-type -Wstrict-aliasing  \
                -Wtrigraphs -Wuninitialized -Wunknown-pragmas           \
                -Wcomment -Wconversion -Wcast-align                     \
                -pedantic -pipe -fstack-protector -Wformat-nonliteral   \
                -Wnon-virtual-dtor -Wreorder -Wenum-compare             \
                -Winvalid-pch -Woverloaded-virtual -Wabi                \

ifeq ($(RELEASE), YES)
CFLAGS		+=	-Werror
CXXFLAGS	+=	-Werror
else
ifeq ($(DEBUG), YES)
CFLAGS		+=	-D DEBUG -g
CXXFLAGS	+=	-D DEBUG -g
endif
endif

ifeq ($(DLL), YES)
CFLAGS 	 +=	-fPIC -ldl
CXXFLAGS +=	-fPIC -ldl
endif
ifeq ($(STATIC), YES)
CFLAGS	 +=	-fPIC
CXXFLAGS +=	-fPIC
endif

ifeq ($(SANITIZE), YES)
CFLAGS	 +=	-fsanitize=memory -fsanitize-memory-track-origins=2 -fomit-frame-pointer
CXXFLAGS +=	-fsanitize=memory -fsanitize-memory-track-origins=2 -fomit-frame-pointer
endif

CC	=	gcc
CXX	=	g++

LDFLAGS	=

ifeq ($(DLL), YES)
CC	+= -shared
CXX	+= -shared
endif

ifeq ($(STATIC), YES)
LINKER = ar -rcs
endif

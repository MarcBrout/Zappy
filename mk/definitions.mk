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

ifeq ($(RELEASE),yes)
CFLAGS		+=	-Werror
CXXFLAGS	+=	-Werror
else
ifeq ($(DEBUG),yes)
CFLAGS		+=	-D DEBUG -g
CXXFLAGS	+=	-D DEBUG -g
endif
endif

ifeq ($(DLL),yes)
CFLAGS 	 +=	-fPIC -ldl
CXXFLAGS +=	-fPIC -ldl
endif
ifeq ($(STATIC),yes)
CFLAGS	 +=	-fPIC
CXXFLAGS +=	-fPIC
endif

ifeq ($(SANITIZE),yes)
CFLAGS	 +=	-fsanitize=address -fomit-frame-pointer -fsanitize=undefined -g3
CXXFLAGS	 +=	-fsanitize=address -fomit-frame-pointer -g3
LDFLAGS += -lasan
endif

CC	=	gcc
CXX	=	g++

LDFLAGS	=

ifeq ($(DLL),yes)
CC	+= -shared
CXX	+= -shared
endif

ifeq ($(STATIC),yes)
LINKER = ar -rcs
endif

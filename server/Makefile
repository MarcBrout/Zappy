SERVER=		zappy_server

SERVER_FOLDER=	src/

ARGS= argument_processors/argument_

CORE= core/

SERVER_RAW_SRC=	server.c \
				argument_parsing.c \
				help.c \
				$(ARGS)height.c \
				$(ARGS)name.c \
				$(ARGS)nbclients.c \
				$(ARGS)port.c \
				$(ARGS)time.c \
				$(ARGS)width.c \
				$(CORE)circular_buffer.c \
				$(CORE)internationalization.c \
				$(CORE)proceed.c \
				$(CORE)proceed_writes.c \
				$(CORE)server_launch.c \
				$(CORE)socket.c

SERVER_SRC=	$(addprefix $(SERVER_FOLDER), $(SERVER_RAW_SRC))

SERVER_OBJ=	$(SERVER_SRC:.c=.o)

INC=		-I./include

CC=		gcc

CFLAGS=		-W -Wall -Werror -Ofast $(INC)

ifeq ($(DEBUG),yes)
CFLAGS+=	-g3
endif

$(SERVER): $(SERVER_OBJ)
	$(CC) -o $(SERVER) $(SERVER_OBJ) $(INC)

all: $(SERVER)

clean:
	rm -f $(SERVER_OBJ)

fclean: clean
	rm -f $(SERVER)

re: fclean all

.PHONY: all clean fclean re

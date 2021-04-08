NAME = minishell
HEADER = minibash.h

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
LIBS = -ltermcap

SRC = entry_point.c error.c utils.c readline/readline.c readline/handle_keys.c \
		readline/signals.c readline/utils_readline.c readline/handle_execute.c \
		envp/create_lst.c

OBJ = $(SRC:.s=.o)

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	@$(CC) $(CFLAGS) $(LIBS) $(SRC) -o $@
	@echo "\033[1;33m RUN MINISHELL : ./minishell \033[0m"
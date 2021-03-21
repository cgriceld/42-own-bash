NAME = minishell
HEADER = minibash.h

CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIBS = -ltermcap

SRC = entry_point.c error.c utils.c

OBJ = $(SRC:.s=.o)

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	@$(CC) $(CFLAGS) $(LIBS) $(SRC) -o $(NAME)
	@echo "\033[1;33m RUN MINISHELL : ./minishell \033[0m"
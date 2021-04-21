NAME = minishell
HEADER = minibash.h

CC = gcc
CFLAGS = -g
LIBS = -ltermcap

SRC = entry_point.c error.c utils/utils.c utils/ft_split.c \
	readline/handle_execute.c readline/handle_keys.c \
	readline/readline.c readline/signals.c readline/utils_readline.c \
	parser/parse_one.c parser/parse_split.c parser/parser.c \
	parser/parse_redirect.c parser/run_one.c parser/run_pipe.c \
	parser/run_redirect.c \
	envp/envp_to_list.c envp/envp_to_arr.c envp/envp_get_value.c \
	builtins/builtins_*.c envp/envp_set_value.c

OBJ = $(SRC:.s=.o)

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	@$(CC) $(CFLAGS) $(LIBS) $(SRC) -o $@
	@echo "\033[1;33m RUN MINISHELL : ./minishell \033[0m"
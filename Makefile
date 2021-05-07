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
	parser/run_redirect.c parser/parse_quotes.c parser/parse_quotes_utils.c\
	parser/parse_quotes_utils2.c parser/parse_dollar.c \
	parser/parse_quotes_join.c parser/precheck_syntax.c \
	envp/envp_to_list.c envp/envp_to_arr.c envp/envp_get_value.c \
	builtins/builtins_*.c envp/envp_set_value.c envp/envp_new_value.c \
	utils/ft_lst.c utils/ft_sort_str.c

OBJ = $(SRC:.s=.o)

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	@$(CC) $(CFLAGS) $(LIBS) $(SRC) -o $@
	@echo "\033[1;33m RUN MINISHELL : ./minishell \033[0m"

clean:
	@/bin/rm -f $(OBJ)
	@echo "\033[1;32m OBJECT FILES DELETED \033[0m"

fclean: clean
	@/bin/rm -f $(NAME)
	@echo "\033[1;32m EXECUTABLE MINISHELL DELETED \033[0m"

re: fclean all

.PHONY: all clean fclean re
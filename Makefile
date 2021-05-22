NAME = minishell
HEADER = minibash.h

CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIBS = -ltermcap

SRC = entry_point.c error.c utils/utils.c utils/ft_split.c \
	readline/handle_execute.c readline/handle_keys.c \
	readline/readline.c readline/signals.c readline/utils_readline.c \
	parser/parse_one.c parser/parse_split.c parser/parse_split_utils.c parser/parser.c \
	parser/parse_redirect.c parser/parse_redirect_utils.c parser/run_one.c parser/run_pipe.c \
	parser/run_one_utils.c parser/run_redirect.c parser/parse_quotes.c parser/parse_quotes_utils.c \
	parser/parse_quotes_utils2.c parser/parse_dollar.c parser/parse_dollar_utils.c \
	parser/parse_quotes_join.c parser/parse_quotes_join_utils.c parser/precheck_syntax.c \
	parser/precheck_syntax_utils.c envp/envp_to_list.c envp/envp_to_arr.c envp/envp_get_value.c \
	builtins/builtins_cd.c builtins/builtins_echo.c builtins/builtins_env.c \
	builtins/builtins_exit.c builtins/builtins_export.c builtins/builtins_export_2.c  \
	builtins/builtins_pwd.c builtins/builtins_unset.c \
	builtins/redir.c envp/envp_set_value.c envp/envp_new_value.c \
	utils/ft_lst.c utils/ft_sort_str.c \
	utils/utils1.c utils/utils2.c utils/utils3.c utils/utils4.c utils/utils5.c utils/utils6.c

OBJ = $(SRC:.c=.o)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

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
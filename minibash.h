#ifndef MINIBASH_H
# define MINIBASH_H

#include <term.h>
#include <unistd.h>
#include <string.h>
#include <curses.h>
#include <stdlib.h>
#include <stdio.h>
#include <termcap.h>
#include <strings.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

// errors
#define WRONG_ARGS "wrong input arguments, should be : ./minishell"

// reader defines
#define PROMPT "\033[1;36mminibash\033[0m : "
#define UP "\e[A"
#define DOWN "\e[B"
#define LEFT "\e[C"
#define RIGHT "\e[D"
#define DEL "\x7f"
#define CTRLD "\04"

int was_signal;

// terminal modes
typedef enum	e_modes
{
	NOT_CANON,
	CANON,
	WAS_SIGN,
	NO_SIGN
}				t_modes;

// history, doubly linked list
typedef struct	s_history
{
	char				*command;
	char				*cache;
	size_t				len;
	size_t				cache_len;
	struct s_history	*prev;
	struct s_history	*next;
}				t_history;

// shell struct with main info
typedef struct	s_shell
{
	t_history	*history;
	t_history	*hist_ptr;
	t_history	*hist_curr;
}				t_shell;

char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_putchar(int c);
size_t	ft_strlen(const char *s);
void	ft_putendl_fd(char *s, int fd);

void lite_error(char *comment);
void free_shell(t_shell **shell);
void free_error(char *comment, t_shell **shell);

#endif
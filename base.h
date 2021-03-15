#ifndef BASE_H
# define BASE_H

#include <term.h>
#include <unistd.h>
#include <string.h>
#include <curses.h>
#include <stdlib.h>
#include <stdio.h>
#include <termcap.h>
#include <strings.h>

#define PROMPT "\033[1;36mminibash\033[0m : "
#define UP "\e[A"
#define DOWN "\e[B"
#define LEFT "\e[C"
#define RIGHT "\e[D"
#define DEL "\x7f"
#define CTRLD "\04"

// doubly linked list
typedef struct	s_history
{
	char				*command;
	size_t				len;
	struct s_history	*prev;
	struct s_history	*next;
}				t_history;

typedef enum	e_termmode
{
	NOT_CANON,
	CANON
}				t_termode;

char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_putchar(int c);
size_t	ft_strlen(const char *s);

#endif
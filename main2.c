#include <term.h>
#include <unistd.h>
#include <string.h>
#include <curses.h>
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	char *dup;
	char *tmp;

	dup = (char *)malloc(strlen(s1) + 1);
	if (!dup)
		return (NULL);
	tmp = dup;
	while (*s1)
		*tmp++ = *s1++;
	*tmp = '\0';
	return (dup);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	char	*tmp;

	if (!s1 || !s2)
		return (NULL);
	join = (char *)malloc(strlen(s1) + strlen(s2) + 1);
	if (!join)
		return (NULL);
	tmp = join;
	while (*s1)
		*tmp++ = *s1++;
	while (*s2)
		*tmp++ = *s2++;
	*tmp = '\0';
	return (join);
}

void prompt(void)
{
	write(1, "minibash : ", strlen("minibash : "));
}

int ft_putchar (int c)
{
	write(1, &c, 1);
}

void arrows(char *str)
{
	if (!strcmp(str, "\e[A"))
	{
		tputs(tgetstr("rc", 0), 1, ft_putchar);
		write(1, "previous", strlen("previous"));
		tputs(tgetstr("ce", 0), 1, ft_putchar);
	}
	else if (!strcmp(str, "\e[B"))
	{
		tputs(tgetstr("rc", 0), 1, ft_putchar);
		write(1, "next", strlen("next"));
		tputs(tgetstr("ce", 0), 1, ft_putchar);
	}
}

int main(int argc, char **argv, char **envp)
{
	char str[21];
	char *comm;
	char *tmp;
	char *del;
	int l;
	struct termios term;

	tcgetattr(0, &term);
	term.c_lflag &= ~(ECHO);
	term.c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, &term);
	char *type = getenv("TERM");
	tgetent(0, type);

	while (1)
	{
		prompt();
		tputs(tgetstr("sc", 0), 1, ft_putchar);
		bzero(str, 21);
		comm = ft_strdup("");

		l = read(0, str, 21);
		if (!strcmp(str, "\04"))
			return (0);
		else if (!strcmp(str, "\n"))
		{
			write(1, str, l);
			continue;
		}
		else if (!strcmp(str, "\e[A") || !strcmp(str, "\e[B"))
			arrows(str);
		else
		{
			write(1, str, l);
			tmp = comm;
			comm = ft_strjoin(comm, str);
			free(tmp);
		}
		while (strcmp(str, "\n") && strcmp(str, "\04"))
		{
			bzero(str, 21);
			l = read(0, str, 21);
			if (!strcmp(str, "\e[A"))
			{
				tputs(tgetstr("rc", 0), 1, ft_putchar);
				tputs(tgetstr("cd", 0), 1, ft_putchar);
				write(1, "previous", strlen("previous"));
			}
			else if (!strcmp(str, "\e[B"))
			{
				tputs(tgetstr("rc", 0), 1, ft_putchar);
				tputs(tgetstr("cd", 0), 1, ft_putchar);
				write(1, "next", strlen("next"));
			}
			else if (!strcmp(str, tgetstr("kb", 0)))
			{
				tputs(tgetstr("le", 0), 1, ft_putchar);
				tputs(tgetstr("dc", 0), 1, ft_putchar);
			}
			else
			{
				write(1, str, l);
				tmp = comm;
				comm = ft_strjoin(comm, str);
				free(tmp);
			}
		}
		if (!strcmp(str, "\n"))
		{
			write(1, comm, strlen(comm));
			free(comm);
		}
		if (!strcmp(str, "\04"))
			return (0);
	}
	write(1, "\n", 1);
	return (0);
}
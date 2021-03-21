#include <term.h>
#include <unistd.h>
#include <string.h>
#include <curses.h>
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>

void prompt(void)
{
	write(1, "minishell : ", strlen("minishell : "));
}

int ft_putchar (int c)
{
	write(1, &c, 1);
}

int main(int argc, char **argv, char **envp)
{
	char str[21];
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
		if (!strcmp(str, "\04"))
			return (0);
		prompt();
		tputs(tgetstr("sc", 0), 1, ft_putchar);
		bzero(str, 21);
		l = read(0, str, 21);
		if (!strcmp(str, "\04"))
		return (0);
		else if (!strcmp(str, "\n"))
		{
			write(1, str, l);
			continue;
		}
		else
			write(1, str, l);
		while (strcmp(str, "\n") && strcmp(str, "\04"))
		{
			bzero(str, 21);
			l = read(0, str, 21);
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
			else if (!strcmp(str, tgetstr("kb", 0)))
			{
				tputs(tgetstr("le", 0), 1, ft_putchar);
				tputs(tgetstr("dc", 0), 1, ft_putchar);
			}
			else
				write(1, str, l);
		}
	}
	write(1, "\n", 1);
	return (0);
}

// left/right arrow bound?

// #include <term.h>
// #include <unistd.h>

// int main(int argc, char **argv, char **envp)
// {
// 	char str[21];
// 	int l;
// 	struct termios term;

// 	tcgetattr(0, &term);
// 	term.c_lflag &= ~(ECHO);
// 	term.c_lflag &= ~(ICANON);
// 	// term.c_cc[VMIN] = 1;
// 	// term.c_cc[VTIME] = 0;
// 	tcsetattr(0, TCSANOW, &term);

// 	l = read(0, str, 21);
// 	write(1, str, l);
// 	write(1, "\n", 1);
// 	return (0);
// }

// #include <term.h>
// #include <unistd.h>
// #include <string.h>
// #include <curses.h>
// #include <strings.h>

// int main(int argc, char **argv, char **envp)
// {
// 	char str[21];
// 	int l;
// 	struct termios term;

// 	tcgetattr(0, &term);
// 	term.c_lflag &= ~(ECHO); // будет ли фукнция read отображать набираемые символы
// 	term.c_lflag &= ~(ICANON);
// 	// term.c_cc[VMIN] = 1; // минимально один символ, нажали 1 символ и read прервался
// 	// term.c_cc[VTIME] = 0; // ожидать не надо
// 	tcsetattr(0, TCSANOW, &term);
// 	tgetent(0, "xterm-256color");
	
// 	do
// 	{
// 	    bzero(str, 21);
// 	    l = read(0, str, 21);
// 	    char *s = tgetstr("kd", 0);
// 	    if (!strcmp(str, "\e[A"))
// 	        write(1, "previous", strlen("previous"));
// 	    else if (!strcmp(str, "\e[B"))
// 	        write(1, "next", strlen("next"));
// 	    else
// 	        write(1, str, l);
// 	} while (strcmp(str, "\n"));
// 	write(1, "\n", 1);
// 	return (0);
// }
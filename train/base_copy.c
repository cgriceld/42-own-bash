#include "base.h"

// CHANGE STRCMP TP FT_STRCMP, BZERO

static void set_mode(struct termios term, int type)
{
	tcgetattr(0, &term);
	!type ? (term.c_lflag &= ~(ECHO | ICANON)) : (term.c_lflag |= (ECHO | ICANON));
	tcsetattr(0, TCSANOW, &term);
}

static void prompt(void)
{
	write(1, PROMPT, ft_strlen(PROMPT));
}

int main(int argc, char **argv, char **envp)
{
	struct termios term;
	char *type; // terminal type
	char str[10];
	t_history *first, *tmp_hist, *hist_ptr;
	size_t read_len, comm_len;
	char *tmp, *cache;

	set_mode(term, NOT_CANON);
	type = getenv("TERM");
	tgetent(0, type);

	first = (t_history *)malloc(sizeof(t_history));
	if (!first)
		return (0);
	tmp_hist = first;
	tmp_hist->command = ft_strdup("");
	tmp_hist->next = NULL;
	tmp_hist->prev = NULL;
	tmp_hist->len = 0;
	hist_ptr = tmp_hist;

	bzero(str, 10);
	cache = NULL;

	prompt();
	
	while (strcmp(str, CTRLD))
	{
		if (!strcmp(str, "\n"))
			prompt();
		bzero(str, 10);
		read_len = read(0, str, 10);
		if (!strcmp(str, LEFT) || !strcmp(str, RIGHT))
			continue;
		else if (!strcmp(str, UP))
		{
			if (!hist_ptr->prev)
				continue;
			comm_len = hist_ptr->len;
			while (comm_len)
			{
				tputs(tgetstr("le", 0), 1, ft_putchar); // String to move the cursor left one column
				comm_len--;
			}
			tputs(tgetstr("cd", 0), 1, ft_putchar); // String to clear the line the cursor is on, and following lines
			write(1, hist_ptr->prev->command, hist_ptr->prev->len);
			hist_ptr = hist_ptr->prev;
		}
		else if (!strcmp(str, DOWN))
		{
			if (!hist_ptr->next)
				continue;
			comm_len = hist_ptr->len;
			while (comm_len)
			{
				tputs(tgetstr("le", 0), 1, ft_putchar); // String to move the cursor left one column
				comm_len--;
			}
			tputs(tgetstr("cd", 0), 1, ft_putchar); // String to clear the line the cursor is on, and following lines
			write(1, hist_ptr->next->command, hist_ptr->next->len);
			hist_ptr = hist_ptr->next;
		}
		else if (!strcmp(str, DEL))
		{
			if (!hist_ptr->len)
				continue;
			tputs(tgetstr("le", 0), 1, ft_putchar); // String to move the cursor left one column
			tputs(tgetstr("dc", 0), 1, ft_putchar); // String to delete one character position at the cursor
			hist_ptr->command[--hist_ptr->len] = '\0';
			tmp = hist_ptr->command;
			hist_ptr->command = ft_strdup(hist_ptr->command);
			free(tmp);
		}
		else if (!strcmp(str, "\n"))
		{
			write(1, "\n", 1);
			if (hist_ptr != tmp_hist)
			{
				tmp = tmp_hist->command;
				tmp_hist->command = ft_strdup(hist_ptr->command);
				free(tmp);
				tmp_hist->len = hist_ptr->len;
			}
			if (tmp_hist->len)
			{
				write(1, tmp_hist->command, tmp_hist->len);
				tmp_hist->next = (t_history *)malloc(sizeof(t_history));
				if (!tmp_hist->next)
					return (0);
				tmp_hist->next->prev = tmp_hist;
				tmp_hist = tmp_hist->next;
				tmp_hist->command = ft_strdup("");
				tmp_hist->len = 0;
				tmp_hist->next = NULL;
				hist_ptr = tmp_hist;
				write(1, "\n", 1);
			}
		}
		else
		{
			write(1, str, read_len);
			tmp = hist_ptr->command;
			hist_ptr->command = ft_strjoin(hist_ptr->command, str);
			free(tmp);
			hist_ptr->len++;
		}
	}
	set_mode(term, CANON);
	write(1, "\n", 1);
	return (0);
}

// int main(int argc, char **argv, char **envp)
// {
// 	char str[10];
// 	char *type;
// 	char *comm;
// 	char *tmp;
// 	char *del;
// 	int l;
// 	struct termios term;
// 	int len;
// 	int h, w;

// 	set_notcanon(term);
// 	type = getenv("TERM");
// 	tgetent(0, type);
// 	while (1)
// 	{
// 		if (strcmp(str, "\x7f") && strcmp(str, "\e[C") && strcmp(str, "\e[D"))
// 			prompt();

// 		bzero(str, 10);
// 		comm = ft_strdup("");

// 		l = read(0, str, 10);
// 		len = 0;
// 		if (!strcmp(str, "\04"))
// 		{
// 			set_canon(term);
// 			write(1, "\n", 1);
// 			return (0);
// 		}
// 		else if (!strcmp(str, "\x7f"))
// 			continue;
// 		else if (!strcmp(str, "\n"))
// 		{
// 			write(1, "\n", 1);
// 			continue;
// 		}
// 		else if (!strcmp(str, "\e[C") || !strcmp(str, "\e[D"))
// 			continue;
// 		else if (!strcmp(str, "\e[A") || !strcmp(str, "\e[B"))
// 			arrows(str, &len);
// 		else
// 		{
// 			write(1, str, l);
// 			tmp = comm;
// 			comm = ft_strjoin(comm, str);
// 			free(tmp);
// 			len++;
// 		}
// 		while (strcmp(str, "\n") && strcmp(str, "\04"))
// 		{
// 			bzero(str, 10);
// 			l = read(0, str, 10);
// 			if (!strcmp(str, "\e[C") || !strcmp(str, "\e[D"))
// 				continue;
// 			if (!strcmp(str, "\e[A"))
// 			{
// 				while (len)
// 				{
// 					tputs(tgetstr("le", 0), 1, ft_putchar);
// 					len--;
// 				}
// 				tputs(tgetstr("cd", 0), 1, ft_putchar);
// 				write(1, "previous", strlen("previous"));
// 			}
// 			else if (!strcmp(str, "\e[B"))
// 			{
// 				while (len)
// 				{
// 					tputs(tgetstr("le", 0), 1, ft_putchar);
// 					tputs(tgetstr("dc", 0), 1, ft_putchar);
// 					len--;
// 				}
// 				write(1, "next", strlen("next"));
// 			}
// 			else if (!strcmp(str, "\x7f"))
// 			{
// 				if (!len)
// 					continue;
// 				tputs(tgetstr("le", 0), 1, ft_putchar);
// 				tputs(tgetstr("dc", 0), 1, ft_putchar);
// 				len--;
// 			}
// 			else if (!strcmp(str, "\n"))
// 			{
// 				write(1, "\n", 1);
// 				write(1, comm, len);
// 				free(comm);
// 			}
// 			else
// 			{
// 				write(1, str, l);
// 				tmp = comm;
// 				comm = ft_strjoin(comm, str);
// 				free(tmp);
// 				len++;
// 			}
// 		}
// 		if (!strcmp(str, "\04"))
// 		{
// 			set_canon(term);
// 			write(1, "\n", 1);
// 			return (0);
// 		}
// 		else
// 			write(1, "\n", 1);
// 	}
// 	return (0);
// }
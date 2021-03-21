#include "minibash.h"

static void set_mode(int type)
{
	struct termios term;

	tcgetattr(0, &term);
	!type ? (term.c_lflag &= ~(ECHO | ICANON)) : (term.c_lflag |= (ECHO | ICANON));
	tcsetattr(0, TCSANOW, &term);
}

static void prompt(void)
{
	write(1, PROMPT, ft_strlen(PROMPT));
}

static void init_hist(t_shell *shell)
{
	shell->hist_curr->command = ft_strdup("");
	if (!shell->hist_curr->command)
		free_error(strerror(errno), &shell);
	shell->hist_curr->cache = NULL;
	shell->hist_curr->len = 0;
	shell->hist_curr->cache_len = 0;
	shell->hist_curr->next = NULL;
}

static int *signal_tracker(void)
{
	static int was_sig = 0;

	return (&was_sig);
}

static void handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		prompt();
		*signal_tracker() = 1;
	}
	return;
}

static void set_signals(void)
{
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
}

static void external(char *run, char **argv, char **envp)
{
	pid_t	pid;
	int		res;
	int		status;

	pid = fork();
	if (!pid)
	{
		res = execve(run, argv, envp);
		if (res < 0)
			printf("%s\n", strerror(errno));
		exit(res);
	}
	else
		waitpid(pid, &status, 0);
}

static void handle_up(t_shell *shell)
{
	size_t comm_len;

	if (!shell->hist_ptr->prev)
		return;
	comm_len = shell->hist_ptr->len;
	while (comm_len)
	{
		tputs(tgetstr("le", 0), 1, ft_putchar);				// String to move the cursor left one column
		comm_len--;
	}
	tputs(tgetstr("cd", 0), 1, ft_putchar);					// String to clear the line the cursor is on, and following lines
	write(1, shell->hist_ptr->prev->command, shell->hist_ptr->prev->len);
	shell->hist_ptr = shell->hist_ptr->prev;
}

static void handle_down(t_shell *shell)
{
	size_t comm_len;

	if (!shell->hist_ptr->next)
		return;
	comm_len = shell->hist_ptr->len;
	while (comm_len)
	{
		tputs(tgetstr("le", 0), 1, ft_putchar);
		comm_len--;
	}
	tputs(tgetstr("cd", 0), 1, ft_putchar);
	write(1, shell->hist_ptr->next->command, shell->hist_ptr->next->len);
	shell->hist_ptr = shell->hist_ptr->next;
}

static void handle_del(t_shell *shell)
{
	char *tmp;

	if (!shell->hist_ptr->len)
		return;
	tputs(tgetstr("le", 0), 1, ft_putchar);		// String to move the cursor left one column
	tputs(tgetstr("dc", 0), 1, ft_putchar);		// String to delete one character position at the cursor
	if (shell->hist_ptr != shell->hist_curr && !shell->hist_ptr->cache)
	{
		shell->hist_ptr->cache = ft_strdup(shell->hist_ptr->command);
		if (!shell->hist_ptr->cache)
			free_error(strerror(errno), &shell);
		shell->hist_ptr->cache_len = shell->hist_ptr->len;
	}
	shell->hist_ptr->command[--shell->hist_ptr->len] = '\0';
	tmp = shell->hist_ptr->command;
	shell->hist_ptr->command = ft_strdup(shell->hist_ptr->command);
	free(tmp);
}

static void handle_execute(t_shell *shell, char **envp, char **argv)
{
	char *tmp;

	if (shell->hist_ptr->len)
		printf("\n");
	if (shell->hist_ptr != shell->hist_curr)
	{
		tmp = shell->hist_curr->command;
		shell->hist_curr->command = ft_strdup(shell->hist_ptr->command);
		free(tmp);
		shell->hist_curr->len = shell->hist_ptr->len;
		if (shell->hist_ptr->cache)
		{
			tmp = shell->hist_ptr->command;
			shell->hist_ptr->command = ft_strdup(shell->hist_ptr->cache);
			free(tmp);
			free(shell->hist_ptr->cache);
			shell->hist_ptr->cache = NULL;
			shell->hist_ptr->len = shell->hist_ptr->cache_len;
		}
	}
	if (shell->hist_curr->len)
	{
		if (!strcmp(shell->hist_curr->command, "/bin/ls") || !strcmp(shell->hist_curr->command, "/bin/cat"))
			external(shell->hist_curr->command, argv, envp);
		else
			write(1, shell->hist_curr->command, shell->hist_curr->len);
		shell->hist_curr->next = (t_history *)malloc(sizeof(t_history));
		if (!shell->hist_curr->next)
			free_error(strerror(errno), &shell);
		shell->hist_curr->next->prev = shell->hist_curr;
		shell->hist_curr = shell->hist_curr->next;
		init_hist(shell);
	}
	shell->hist_ptr = shell->hist_curr;
}

static void handle_read(t_shell *shell, char **envp, char **argv, ssize_t read_len, char *str)
{
	char *tmp;

	if (!strcmp(str, LEFT) || !strcmp(str, RIGHT))
		return;
	else if (!strcmp(str, UP))
		handle_up(shell);
	else if (!strcmp(str, DOWN))
		handle_down(shell);
	else if (!strcmp(str, DEL))
		handle_del(shell);
	else if (!strcmp(str, "\n"))
		handle_execute(shell, envp, argv);
	else
	{
		write(1, str, read_len);
		if (shell->hist_ptr != shell->hist_curr && !shell->hist_ptr->cache)
		{
			shell->hist_ptr->cache = ft_strdup(shell->hist_ptr->command);
			if (!shell->hist_ptr->cache)
				free_error(strerror(errno), &shell);
			shell->hist_ptr->cache_len = shell->hist_ptr->len;
		}
		tmp = shell->hist_ptr->command;
		shell->hist_ptr->command = ft_strjoin(shell->hist_ptr->command, str);
		free(tmp);
		shell->hist_ptr->len++;
	}
}

static void ft_readline(char **envp, char **argv, t_shell *shell)
{
	char			str[10];
	ssize_t			read_len;
	char			*tmp;

	bzero(str, 10);
	prompt();
	while (strcmp(str, CTRLD))
	{
		if (!strcmp(str, "\n") && !*signal_tracker())
		{
			printf("\n");
			prompt();
		}
		*signal_tracker() = 0;
		bzero(str, 10);
		set_mode(NOT_CANON);
		read_len = read(0, str, 10);
		if (*signal_tracker() && shell->hist_curr->len)
		{
			tmp = shell->hist_curr->command;
			init_hist(shell);
			free(tmp);
			shell->hist_ptr = shell->hist_curr;
			continue;
		}
		*signal_tracker() = 0;
		set_mode(CANON);
		handle_read(shell, envp, argv, read_len, str);
	}
	printf("\n");
}

static void prepare(int argc, t_shell **shell)
{
	if (argc != 1)
		lite_error(WRONG_ARGS);
	*shell = (t_shell *)malloc(sizeof(t_shell));
	if (!*shell)
		lite_error(strerror(errno));
	(*shell)->history = (t_history *)malloc(sizeof(t_history));
	if (!(*shell)->history)
		free_error(strerror(errno), shell);
	(*shell)->history->prev = NULL; // first node
	(*shell)->hist_curr = (*shell)->history;
	(*shell)->hist_ptr = (*shell)->history;
	init_hist(*shell);
}

int main(int argc, char **argv, char **envp)
{
	t_shell			*shell;

	prepare(argc, &shell);
	tgetent(NULL, getenv("TERM")); // can return -1 in error
	set_signals();
	ft_readline(envp, argv, shell);
	free_shell(&shell);
	return (0);
}
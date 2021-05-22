#include "../minibash.h"

static void	write_symbol(t_shell *shell, char *str, ssize_t read_len)
{
	char	*tmp;

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

static void	handle_read(t_shell *shell, char *str, ssize_t read_len)
{
	if (!ft_strncmp(str, LEFT, 10) || !ft_strncmp(str, RIGHT, 10))
		return ;
	else if (!ft_strncmp(str, UP, 10))
		handle_up(shell);
	else if (!ft_strncmp(str, DOWN, 10))
		handle_down(shell);
	else if (!ft_strncmp(str, DEL, 10))
		handle_del(shell);
	else if (!ft_strncmp(str, "\n", 10))
		handle_execute(shell);
	else
		write_symbol(shell, str, read_len);
}

void	deal_cache(t_shell *shell)
{
	char	*tmp;

	tmp = shell->hist_ptr->command;
	shell->hist_ptr->command = ft_strdup(shell->hist_ptr->cache);
	free(tmp);
	free(shell->hist_ptr->cache);
	shell->hist_ptr->cache = NULL;
	shell->hist_ptr->len = shell->hist_ptr->cache_len;
}

static void	ctrlc(t_shell *shell)
{
	char	*tmp;

	if ((shell->hist_ptr != shell->hist_curr) && shell->hist_ptr->cache)
		deal_cache(shell);
	tmp = shell->hist_curr->command;
	init_hist(shell);
	free(tmp);
	shell->hist_ptr = shell->hist_curr;
}

void	ft_readline(t_shell *shell, ssize_t read_len)
{
	char	str[10];

	ft_bzero(str, 10);
	prompt();
	while (1)
	{
		if (!ft_strncmp(str, "\n", 10) && !*signal_tracker())
			prompt();
		ft_bzero(str, 10);
		set_mode(NOT_CANON);
		read_len = read(0, str, 10);
		if (!ft_strncmp(str, CTRLD, 10) && shell->hist_ptr->command[0] == '\0')
		{
			write(1, "exit", 4);
			break ;
		}
		if (!ft_strncmp(str, CTRLD, 10))
			continue ;
		set_mode(CANON);
		if (*signal_tracker())
			ctrlc(shell);
		*signal_tracker() = 0;
		handle_read(shell, str, read_len);
	}
	printf("\n");
}

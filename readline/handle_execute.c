#include "../minibash.h"

static int	is_builtin(t_shell *shell)
{
	if (!ft_strncmp(shell->hist_curr->command, "echo", shell->hist_curr->len))
		return (builtins_echo(shell));
	else if (!ft_strncmp(shell->hist_curr->command, "cd", shell->hist_curr->len))
		return (builtins_cd(shell));
	else if (!ft_strncmp(shell->hist_curr->command, "pwd", shell->hist_curr->len))
		return (builtins_pwd(shell));
	else if (!ft_strncmp(shell->hist_curr->command, "env", shell->hist_curr->len))
		return (builtins_env(shell));
	else if (!ft_strncmp(shell->hist_curr->command, "unset", shell->hist_curr->len))
		return (builtins_unset_value(shell));
	else if (!ft_strncmp(shell->hist_curr->command, "export", shell->hist_curr->len))
		return (builtins_export(shell));
	else if (!ft_strncmp(shell->hist_curr->command, "exit", shell->hist_curr->len))
		return (builtins_exit(shell));
	else
		return (-1);
}

void		handle_execute(t_shell *shell)
{
	char *tmp;

	if (shell->hist_ptr->len)
		printf("\n");
	ret_status = 0; // new command
	if (shell->hist_ptr != shell->hist_curr)
	{
		tmp = shell->hist_curr->command;
		shell->hist_curr->command = ft_strdup(shell->hist_ptr->command);
		free(tmp);
		shell->hist_curr->len = shell->hist_ptr->len;
		if (shell->hist_ptr->cache)
			deal_cache(shell);
	}
	if (shell->hist_curr->len)
	{
		if (is_builtin(shell) == -1)
			find_external(shell);
		shell->hist_curr->next = (t_history *)malloc(sizeof(t_history));
		if (!shell->hist_curr->next)
			free_error(strerror(errno), &shell);
		shell->hist_curr->next->prev = shell->hist_curr;
		shell->hist_curr = shell->hist_curr->next;
		init_hist(shell);
	}
	shell->hist_ptr = shell->hist_curr;
}
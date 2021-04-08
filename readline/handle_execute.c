#include "../minibash.h"

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

void handle_execute(t_shell *shell, char **envp, char **argv)
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
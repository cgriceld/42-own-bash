#include "../minibash.h"

static void	run_external(char *comm, char **arr_env)
{
	pid_t	pid;
	int		res;
	int		status;

	char *args[] = {comm, NULL}; // test
	pid = fork();
	if (pid < 0)
	{
		printf("%s\n", strerror(errno));
		ret_status = errno;
	}
	if (!pid) // child
	{
		res = execve(comm, args, arr_env);
		if (res < 0)
			printf("%s\n", strerror(errno));
		exit(res);
	}
	else // parent
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			ret_status = WEXITSTATUS(status);
		else
			ret_status = 1;
	}
}

static void	free_split(char ***split, t_shell *shell)
{
	ft_twodarr_free(split, ft_twodarr_len(*split));
	free_error(strerror(errno), &shell);
}

static void	check_external(char *comm, t_shell *shell, char **arr_env, int flag)
{
	run_external(comm, arr_env);
	if (flag == SHORT_PATH)
		free(comm);
	ft_twodarr_free(&arr_env, shell->env_size);
}


void			find_external(t_shell *shell)
{
	struct stat	s;
	char		**split;
	char		*tmp;
	char		*comm;
	size_t		i;

	if (!stat(shell->hist_curr->command, &s)) // if absolute path
	{
		check_external(shell->hist_curr->command, shell, envp_to_arr(shell), FULL_PATH);
		return;
	}
	tmp = envp_get_value(shell, "PATH");
	if (!tmp) // unset PATH
	{
		// printf
		printf("%s%s%s\n", "-minibash: ", shell->hist_curr->command, ": command not found");
		ret_status = 127;
		return;
	}
	split = ft_split(tmp, ':');
	if (!split)
		free_error(strerror(errno), &shell);
	i = 0;
	while (split[i])
	{
		tmp = ft_strjoin(split[i], "/");
		if (!tmp)
			free_split(&split, shell);
		comm = ft_strjoin(tmp, shell->hist_curr->command);
		free(tmp);
		if (!comm)
			free_split(&split, shell);
		if (!stat(comm, &s))
		{
			ft_twodarr_free(&split, ft_twodarr_len(split));
			check_external(comm, shell, envp_to_arr(shell), SHORT_PATH);
			return;
		}
		free(comm);
		i++;
	}
	ft_twodarr_free(&split, ft_twodarr_len(split));
	if (ft_strchr(shell->hist_curr->command, '/'))
		// printf
		printf("%s%s%s\n", "-minibash: ", shell->hist_curr->command, ": No such file or directory");
	else
		// printf
		printf("%s%s%s\n", "-minibash: ", shell->hist_curr->command, ": command not found");
	ret_status = 127;
}
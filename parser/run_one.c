#include "../minibash.h"

static int run_builtin(t_seq *tmp_seq)
{
	write(1, tmp_seq->run, ft_strlen(tmp_seq->run));
	printf("\n");
	return (0);
}

static void handle_errno(char *comm)
{
	if (errno == ENOENT)
	{
		write(2, "-minibash: ", ft_strlen("-minibash: "));
		write(2, comm, ft_strlen(comm));
		write(2, ": command not found\n", ft_strlen(": command not found\n"));
	}
	else
		write(2, strerror(errno), ft_strlen(strerror(errno)));
}

static int run_execve(pid_t pid, t_seq *tmp_seq, char **arr_env, t_shell *shell)
{
	int res;
	int status;

	if (!pid)
	{
		res = execve(tmp_seq->run, tmp_seq->args, arr_env);
		if (res < 0)
			handle_errno(tmp_seq->run);
		exit(res);
	}
	else
	{
		waitpid(pid, &status, 0);
		ft_twodarr_free(&arr_env, shell->env_size);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		else
			return (1);
	}
}

static int run_external(t_seq *tmp_seq, t_shell *shell, char **arr_env)
{
	pid_t pid;

	pid = fork();
	if (pid < 0)
	{
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		ft_twodarr_free(&arr_env, shell->env_size);
		return (errno);
	}
	else
		return (run_execve(pid, tmp_seq, arr_env, shell));
}

int run_one(t_seq *tmp_seq, t_shell *shell)
{
	if (is_builtin(tmp_seq->run))
		return (run_builtin(tmp_seq));
	else
		return (run_external(tmp_seq, shell, envp_to_arr(shell)));
}
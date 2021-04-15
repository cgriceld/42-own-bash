#include "../minibash.h"

static void run_builtin(t_seq *tmp_seq)
{
	write(1, tmp_seq->run, ft_strlen(tmp_seq->run));
	printf("\n");
}

static void exec_error(char *run)
{
	if (errno == ENOENT)
	{
		printf("%s%s%s\n", "-minibash: ", run, ": command not found");
		ret_status = 127;
	}
	else
		printf("%s\n", strerror(errno));
}

static void run_execve(pid_t pid, t_seq *tmp_seq, char **arr_env)
{
	int res;
	int status;

	if (!pid)
	{
		res = execve(tmp_seq->run, tmp_seq->args, arr_env);
		if (res < 0)
			exec_error(tmp_seq->run);
		exit(res);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (!ret_status)
		{
			if (WIFEXITED(status))
				ret_status = WEXITSTATUS(status);
			else
				ret_status = 1;
		}
	}
}

static void run_external(t_seq *tmp_seq, t_shell *shell, char **arr_env)
{
	pid_t pid;

	pid = fork();
	if (pid < 0)
	{
		printf("%s\n", strerror(errno));
		ret_status = errno;
		ft_twodarr_free(&arr_env, shell->env_size);
		return;
	}
	else
		run_execve(pid, tmp_seq, arr_env);
	ft_twodarr_free(&arr_env, shell->env_size);
}

int run_one(t_seq *tmp_seq, t_shell *shell)
{
	if (is_builtin(tmp_seq->run))
		run_builtin(tmp_seq);
	else
		run_external(tmp_seq, shell, envp_to_arr(shell));
	return (ret_status);
}
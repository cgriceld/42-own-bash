#include "../minibash.h"

static int run_builtin(t_seq *tmp_seq, t_shell *shell)
{
	char *tmp;

	tmp = ft_low_str(tmp_seq->run);
	printf("%s\n", tmp);
	if (!ft_strncmp(tmp, "echo", ft_strlen(tmp_seq->run)))
		return (builtins_echo(shell, tmp_seq, tmp));
	else if (!ft_strncmp(tmp, "cd", ft_strlen(tmp_seq->run)))
		return (builtins_cd(shell, tmp_seq, tmp));
	else if (!ft_strncmp(tmp, "pwd", ft_strlen(tmp_seq->run)))
		return (builtins_pwd(shell, tmp_seq, tmp));
	else if (!ft_strncmp(tmp, "env", ft_strlen(tmp_seq->run)))
		return (builtins_env(shell, tmp_seq, tmp));
	else if (!ft_strncmp(tmp_seq->run, "unset", ft_strlen(tmp_seq->run)))
		return (builtins_unset_value(shell, tmp_seq, tmp));
	else if (!ft_strncmp(tmp_seq->run, "export", ft_strlen(tmp_seq->run)))
		return (builtins_export(shell, tmp_seq, tmp));
	else if (!ft_strncmp(tmp_seq->run, "exit", ft_strlen(tmp_seq->run)))
		return (builtins_exit(shell, tmp_seq, tmp));
	//printf("\n");
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

static int redirect_out(t_seq *tmp_seq, t_shell *shell)
{
	int fd;

	fd = open(tmp_seq->output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		free_error(strerror(errno), &shell);
	if (tmp_seq->run)
		dup2(fd, 1);
	close(fd);
	return (0);
}

static int redirect_in(t_seq *tmp_seq, t_shell *shell)
{
	int fd;

	fd = open(tmp_seq->input, O_RDONLY, 0644);
	if (fd < 0)
		free_error(strerror(errno), &shell);
	if (tmp_seq->run)
		dup2(fd, 0);
	close(fd);
	return (0);
}

static int run_execve(pid_t pid, t_seq *tmp_seq, char **arr_env, t_shell *shell)
{
	int res;
	int status;

	if (!pid)
	{
		if (tmp_seq->output)
			redirect_out(tmp_seq, shell);
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
	if (!tmp_seq->run)
	{
		if (tmp_seq->info & REDIR_OUT)
			return (redirect_out(tmp_seq, shell));
		if (tmp_seq->info & REDIR_IN)
			return (redirect_in(tmp_seq, shell));
	}
	printf("run_builtin\n");
	if (is_builtin(tmp_seq->run))
		return (run_builtin(tmp_seq, shell));
	else
		return (run_external(tmp_seq, shell, envp_to_arr(shell)));
}
#include "../minibash.h"

static int run_builtin(t_seq *tmp_seq, t_shell *shell)
{
	char *tmp;

	tmp = ft_low_str(tmp_seq->run);
	if (!ft_strncmp(tmp, "echo", ft_strlen(tmp_seq->run)))
		return (builtins_echo(shell, tmp_seq, tmp));
	else if (!ft_strncmp(tmp_seq->run, "cd", ft_strlen(tmp_seq->run)))
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
	return (0);
}

static void handle_eacces(char *comm)
{
	struct stat s;

	if (!ft_strchr(comm, '/'))
	{
		write(2, ": command not found\n", 20);
		exit(127);
	}
	if (!stat(comm, &s) && S_ISDIR(s.st_mode))
		write(2, ": is a directory\n", 17);
	else
		write(2, ": Permission denied\n", 20);
	exit(126);
}

static void handle_errno(char *comm, int errno_save)
{
	write(2, "-minibash: ", 11);
	write(2, comm, ft_strlen(comm));
	if (errno_save == ENOENT)
	{
		if (ft_strchr(comm, '/'))
			write(2, ": No such file or directory\n", 28);
		else
			write(2, ": command not found\n", 20);
		exit(127);
	}
	else if (errno_save == ENOTDIR)
	{
		write(2, ": Not a directory\n", 18);
		exit(126);
	}
	else if (errno_save == EACCES)
		handle_eacces(comm);
	else
	{
		write(2, ": ", 2);
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
		exit(errno_save);
	}
}

// handle_errno(tmp_seq->run, errno);
static int run_execve(pid_t pid, t_seq *tmp_seq, char **arr_env, t_shell *shell)
{
	int status;

	if (!pid)
	{
		if (tmp_seq->redirect && run_redirect(tmp_seq, shell))
			exit(1);
		if (execve(tmp_seq->run, tmp_seq->args, arr_env) < 0)
			handle_errno(tmp_seq->args[0], errno);
		exit(0);
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
	if (!tmp_seq->run && tmp_seq->redirect)
		return (run_redirect(tmp_seq, shell));
	//printf("run_builtin\n");
	if (is_builtin(tmp_seq->run))
		return (run_builtin(tmp_seq, shell));
	else
		return (run_external(tmp_seq, shell, envp_to_arr(shell)));
}
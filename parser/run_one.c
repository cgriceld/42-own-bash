/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_one.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgriceld <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 13:56:26 by cgriceld          #+#    #+#             */
/*   Updated: 2021/05/22 13:56:31 by cgriceld         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

static void	handle_errno(char *comm, int errno_save)
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

static int	run_child(t_seq *tmp_seq, char **arr_env)
{
	if (tmp_seq->redirect && run_redirect(tmp_seq))
		exit(1);
	if (execve(tmp_seq->run, tmp_seq->args, arr_env) < 0)
		handle_errno(tmp_seq->args[0], errno);
	exit(0);
}

static int	run_execve(pid_t pid, t_seq *tmp_seq, char **arr_env, \
					t_shell *shell)
{
	int	status;

	if (!pid)
		run_child(tmp_seq, arr_env);
	else
	{
		waitpid(pid, &status, 0);
		ft_twodarr_free(&arr_env, shell->env_size);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		else if (WIFSIGNALED(status) && WTERMSIG(status) == 2)
			return (130);
		else if (WIFSIGNALED(status) && WTERMSIG(status) == 3)
		{
			write(1, "Quit: 3\n", 8);
			return (131);
		}
		else
			return (1);
	}
	return (0);
}

static int	run_external(t_seq *tmp_seq, t_shell *shell, char **arr_env)
{
	pid_t	pid;

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

int	run_one(t_seq *tmp_seq, t_shell *shell)
{
	if (!tmp_seq->run && tmp_seq->redirect)
		return (run_redirect(tmp_seq));
	if (is_builtin(tmp_seq->run))
		return (run_builtin(tmp_seq, shell));
	else
		return (run_external(tmp_seq, shell, envp_to_arr(shell)));
}

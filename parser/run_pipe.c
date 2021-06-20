#include "../minibash.h"

static void	open_left(t_seq *tmp_seq, t_shell *shell, int *fd)
{
	close(fd[0]);
	dup2(fd[1], 1);
	close(fd[1]);
	exit(run_one(tmp_seq, shell));
}

static int	next_pipe(t_seq *tmp_seq, t_shell *shell)
{
	if (tmp_seq->info & PIPE)
		return (run_pipe(tmp_seq, shell));
	else
		return (run_one(tmp_seq, shell));
}

static void	open_right(t_seq *tmp_seq, t_shell *shell, int *fd)
{
	close(fd[1]);
	dup2(fd[0], 0);
	close(fd[0]);
	exit(next_pipe(tmp_seq, shell));
}

static int	parent_wait(int *fd, int *pid)
{
	int	status;

	close(fd[0]);
	close(fd[1]);
	waitpid(pid[1], &status, 0);
	waitpid(pid[0], NULL, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else
		return (1);
}

int	run_pipe(t_seq *tmp_seq, t_shell *shell)
{
	int		fd[2];
	pid_t	pid[2];

	if (pipe(fd) < 0)
	{
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		return (errno);
	}
	pid[0] = fork();
	if (pid[0] < 0)
	{
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		return (errno);
	}
	if (!pid[0])
		open_left(tmp_seq, shell, fd);
	else
	{
		tmp_seq = tmp_seq->next;
		pid[1] = fork();
		if (!pid[1])
			open_right(tmp_seq, shell, fd);
	}
	return (parent_wait(fd, pid));
}

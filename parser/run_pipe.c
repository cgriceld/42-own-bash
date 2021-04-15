#include "../minibash.h"

static void open_left(t_seq *tmp_seq, t_shell *shell, int *ret, int *fd)
{
	close(fd[0]);
	dup2(fd[1], 1); // stdout now is a copy of fd[1]
	close(fd[1]);
	ret[0] = run_one(tmp_seq, shell);
	exit(ret[0]);
}

static int next_pipe(t_seq *tmp_seq, t_shell *shell)
{
	if (tmp_seq->info & PIPE)
		return (run_pipe(tmp_seq, shell));
	else
		return (run_one(tmp_seq, shell));
}

static void open_right(t_seq *tmp_seq, t_shell *shell, int *ret, int *fd)
{
	close(fd[1]);
	dup2(fd[0], 0); // stdin now is a copy of fd[1]
	close(fd[0]);
	ret[1] = next_pipe(tmp_seq, shell);
	exit(ret[1]);
}

int run_pipe(t_seq *tmp_seq, t_shell *shell)
{
	int fd[2];
	pid_t pid[2];
	int ret[2];
	int status[2];

	pipe(fd); // error if < 0
	pid[0] = fork(); // error if < 0
	if (!pid[0])
		open_left(tmp_seq, shell, ret, fd);
	else
	{
		tmp_seq = tmp_seq->next;
		pid[1] = fork();
		if (!pid[1])
			open_right(tmp_seq, shell, ret, fd);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid[1], &(status[1]), 0);
	waitpid(pid[0], &(status[0]), 0);
	if (WIFEXITED(status[1]))
		ret[1] = WEXITSTATUS(status[1]);
	else
		ret[1] = 1;
	return (ret[1]);
}


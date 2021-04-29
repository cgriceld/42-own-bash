#include "../minibash.h"

static int redirect_error(char *path, int flag)
{
	write(2, "-minibash: ", 11);
	write(2, path, ft_strlen(path));
	if (flag)
		write(2, ": No such file or directory\n", 28);
	if (!flag)
	{
		write(2, ": ", 2);
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
	}
	return (1);
}

int redirect_out(t_seq *tmp_seq, t_shell *shell)
{
	int fd;

	fd = open(tmp_seq->output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (redirect_error(tmp_seq->output, 0));
	if (tmp_seq->run)
		dup2(fd, 1);
	close(fd);
	return (0);
}

int redirect_in(t_seq *tmp_seq, t_shell *shell)
{
	int			fd;
	struct stat	s;

	if (stat(tmp_seq->input, &s))
		return (redirect_error(tmp_seq->input, 1));
	fd = open(tmp_seq->input, O_RDONLY, 0644);
	if (fd < 0)
		return (redirect_error(tmp_seq->input, 0));
	if (tmp_seq->run)
		dup2(fd, 0);
	close(fd);
	return (0);
}
#include "../minibash.h"

int redirect_out(t_seq *tmp_seq, t_shell *shell)
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

int redirect_in(t_seq *tmp_seq, t_shell *shell)
{
	int			fd;
	struct stat	s;

	if (stat(tmp_seq->input, &s))
	{
		write(2, "-minibash: ", ft_strlen("-minibash: "));
		write(2, tmp_seq->input, ft_strlen(tmp_seq->input));
		write(2, ": No such file or directory\n", ft_strlen(": No such file or directory\n"));
		return (1);
	}
	fd = open(tmp_seq->input, O_RDONLY, 0644);
	if (fd < 0)
		free_error(strerror(errno), &shell);
	if (tmp_seq->run)
		dup2(fd, 0);
	close(fd);
	return (0);
}
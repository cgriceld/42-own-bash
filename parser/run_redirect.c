#include "../minibash.h"

static int redirect_error(char *path, int flag)
{
	write(2, "-minibash: ", 11);
	write(2, path, ft_strlen(path));
	if (flag == 1)
		write(2, ": No such file or directory\n", 28);
	else if (flag == 2)
		write(2, ": ambiguous redirect\n", 21);
	else if (!flag)
	{
		write(2, ": ", 2);
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
	}
	return (1);
}

static int redirect_out(t_seq *tmp_seq, t_redir_chain *tmp_redir)
{
	int fd;
	
	if (tmp_redir->type & REDIR_OUT)
		fd = open(tmp_redir->path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(tmp_redir->path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return (redirect_error(tmp_redir->path, 0));
	if (tmp_seq->run && !(tmp_redir->type & IGNORE))
		dup2(fd, 1);
	close(fd);
	return (0);
}

static int redirect_in(t_seq *tmp_seq, t_redir_chain *tmp_redir)
{
	int			fd;
	struct stat	s;

	if (stat(tmp_redir->path, &s))
		return (redirect_error(tmp_redir->path, 1));
	fd = open(tmp_redir->path, O_RDONLY, 0644);
	if (fd < 0)
		return (redirect_error(tmp_redir->path, 0));
	if (tmp_seq->run && !(tmp_redir->type & IGNORE))
		dup2(fd, 0);
	close(fd);
	return (0);
}

int run_redirect(t_seq *tmp_seq, t_shell *shell)
{
	t_redir_chain *tmp_redir;

	tmp_redir = tmp_seq->redirect;
	while (tmp_redir)
	{
		if (tmp_redir->type & AMBIGUOUS)
			return (redirect_error(tmp_redir->path, 2));
		else if ((tmp_redir->type & REDIR_IN) && redirect_in(tmp_seq, tmp_redir))
			return (1);
		else if (((tmp_redir->type & REDIR_OUT) || \
		(tmp_redir->type & REDIR_APPEND)) && redirect_out(tmp_seq, tmp_redir))
			return (1);
		tmp_redir = tmp_redir->next;
	}
	return (0);
}

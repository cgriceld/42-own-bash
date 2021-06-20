#include "../minibash.h"

int	redir(t_seq *tmp_seq, char **str_low, int flag)
{
	static int	fds[2];
	int			res;

	res = 0;
	if (flag != 2)
	{
		fds[0] = dup(0);
		fds[1] = dup(1);
		res = run_redirect(tmp_seq);
	}
	if (flag || res)
	{
		dup2(fds[1], 1);
		dup2(fds[0], 0);
	}
	free(*str_low);
	*str_low = NULL;
	return (res);
}

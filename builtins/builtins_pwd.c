#include "../minibash.h"

char	*pwd(t_shell *shell, t_seq *tmp_seq)
{
	char *buf;
	size_t size;

	buf = NULL;
	size = 0;
	buf = getcwd(buf, size);
	envp_set_value(shell->env, "PWD", buf);
	return (buf);
}

 int	builtins_pwd(t_shell *shell, t_seq *tmp_seq)
{
	char *buf;

	(void)*shell;
	buf = pwd(shell, tmp_seq);
	if (!buf)
		return (-1);
	printf("%s", buf);
	free(buf);
	printf("\n");
	return (0);
}



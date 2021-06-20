#include "../minibash.h"

char	*pwd(t_shell *shell)
{
	char		*buf;
	size_t		size;

	buf = NULL;
	size = 0;
	buf = getcwd(buf, size);
	if (buf)
		envp_set_value(shell, "PWD", buf);
	if (!buf)
		return (ft_strdup(envp_get_value(shell, "PWD")));
	else
		return (buf);
}

int	builtins_pwd(t_shell *shell, t_seq *tmp_seq, char *str_low)
{
	char	*buf;

	if (redir(tmp_seq, &str_low, 0))
		return (1);
	buf = pwd(shell);
	if (!buf)
		return (2);
	printf("%s", buf);
	free(buf);
	printf("\n");
	redir(tmp_seq, &str_low, 2);
	return (0);
}

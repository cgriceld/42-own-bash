#include "../minibash.h"

char	*pwd(t_shell *shell)
{
	char *buf;
	size_t size;

	buf = NULL;
	size = 0;
	buf = getcwd(buf, size);
	//положить полный путь в в текущий эеваермент
	put_the_value(shell->env, buf, "PWD");
	return (buf);
}

 int	print_pwd(t_shell *shell)
{
	char *buf;

	(void)*shell;
	buf = pwd(shell);
	if (!buf)
		return (-1);
	write(1, buf, ft_strlen(buf));
	free(buf);
	return (0);
}



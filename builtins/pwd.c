#include "../minibash.h"

int	put_the_params(t_env env, char *buf, const char *param)
{
	char *tmp;
	int len;

	len = ft_strlen(param);
	while (ft_strncmp(env.key, param, len) != 0)
		env = *env.next;
	tmp = env.value;
	env.value = buf;
	//free(tmp);
	return 0;
}

char	*pwd(t_shell *shell)
{
	char *buf;
	size_t size;

	buf = NULL;
	size = 0;
	buf = getcwd(buf, size);
	//положить полный путь в в текущий эеваермент
	put_the_params(*shell->env, buf, "PWD");
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



#include "../minibash.h"

char	*cd_no_args(char *path)
{
	char **split;
	char *buf[2];
	char *new_path;
	int i;

	split = ft_split(path, '/');
	buf[0] = ft_strjoin("/", split[0]);
	buf[1] = ft_strjoin("/", split[1]);
	new_path = ft_strjoin(buf[0], buf[1]);
	//освободить каждый сплит

	i =  0;
	while (split[i] != 0)
	{
		free(split[i]);
		i++;
	}
	free(split);
	free(buf[0]);
	free(buf[1]);
	return (new_path);
}

int		cd(t_shell *shell)
{
	char *path;
	char *old_path;
	char *param;

	path = NULL;
	param = NULL;
//	param = "builtins";
	(void)*shell;
	old_path = pwd(shell);
	if (!old_path)
		return (-1);
	//если нет параметра;
	if (!param)
		path = cd_no_args(old_path);
	//если есть;
	// НОРМАЛЬНЫЙ ФРИИИ
//	char *tmp;
//	tmp = ft_strjoin(path, "/");
//	path = ft_strjoin(tmp, param);
	chdir(path);
	//положить полный путь в в текущий эеваермент и из текущего в прошлый
	put_the_params(*shell->env, old_path, "OLDPWD");
	put_the_params(*shell->env, path, "PWD");
	return (0);
}

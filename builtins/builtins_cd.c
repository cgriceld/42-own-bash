#include "../minibash.h"

// .
// ..
// - ?

char	*find_path(t_shell *shell, char *path, char *match)
{
	path = envp_get_value(shell, match);
	if (!path)
		printf("cd: %s not set\n", match);
	//free(match);
	return (path);
}

int		builtins_cd(t_shell *shell, t_seq *tmp_seq)
{
	char *path;
	char *old_path;
	char *param;

	param = tmp_seq->args[0];
	old_path = pwd(shell, tmp_seq);
	if (!old_path)
		return (1);
	if (!param)
	{
		path = envp_get_value(shell, "HOME");
		if (!path)
			printf("cd: HOME not set\n");

	}
	else if (ft_strncmp(param, "-", 2) == 0)
	{
		path = envp_get_value(shell, "OLDPWD");
		if (!path)
			printf("cd: OLDPWD not set\n");

	}
	else
		path = param;
	if (chdir(path) != 0)
	{
		printf("cd: %s: No such file or directory\n", param);
		return (1);
	}
	if (envp_set_value(shell->env, old_path, "OLDPWD") != 0)
		envp_new_value(shell, ft_strdup("OLDPWD"), NULL);
	envp_set_value(shell->env, path, "PWD");
	return (0);
}

#include "../minibash.h"

char	*find_path(t_shell *shell, char *path, char *match)
{
	path = envp_get_value(shell, match);
	if (!path)
	{
		printf("cd: %s not set\n", match);
		ret_status = 1;
		return (NULL);
	}
	return (path);
}

void update_pwd(t_shell *shell, char *path, char *old_path, t_seq *tmp_seq)
{
	free(path);
	path = pwd(shell, tmp_seq);
	if (ft_strncmp(old_path, path, ft_strlen(old_path + 1) != 0))
	{
		if (envp_set_value(shell->env, "OLDPWD", old_path) != 0)
			{
				envp_new_value(shell, ft_strdup("OLDPWD"), NULL);
				free(old_path);
			}
		envp_set_value(shell->env, "PWD", path);
	}
}

int		builtins_cd(t_shell *shell, t_seq *tmp_seq)
{
	char *path;
	char *old_path;
	char *param;

	ret_status = 0;
	param = ft_strtrim(tmp_seq->args[1], "\n");
	old_path = pwd(shell, tmp_seq);
	if (!old_path)
		return (1);
	if (!param or (ft_strncmp(param, "", 1) == 0))
		path = find_path(shell, path, "HOME");
	else if (ft_strncmp(param, "-", 2) == 0)
		path = find_path(shell, path, "OLDPWD");
	else
		path = param;
	if (ret_status == 0 && chdir(path) != 0)
	{
		printf("cd: %s: No such file or directory\n", param);
		ret_status = 1;
	}
	//free(param);
	if (ret_status == 0)
		update_pwd(shell, path, old_path, tmp_seq);
	return (ret_status);
}

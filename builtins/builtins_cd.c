#include "../minibash.h"

int		builtins_cd(t_shell *shell)
{
	char *path;
	char *old_path;
	char *param;

	param = NULL;
//	param = "builtins";
//	param = "/Users/sbrenton";
	(void)*shell;
	old_path = pwd(shell);
	if (!old_path)
		return (-1);
	if (!param)
		path = envp_get_value(shell, "HOME");
	else
		path = param;
	if (chdir(path) !=0)
	{
		printf("cd: %s: No such file or directory\n", param);
		return (-1);
	}
	envp_set_value(shell->env, old_path, "OLDPWD");
	envp_set_value(shell->env, path, "PWD");
	return (0);
}

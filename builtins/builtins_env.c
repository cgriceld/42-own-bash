#include "../minibash.h"

int	builtins_env(t_shell *shell, t_seq *tmp_seq, char *str_low)
{
	t_env	*tmp;

	if (redir(tmp_seq, &str_low, 0))
		return (1);
	if (envp_get_value(shell, "PATH") == NULL)
	{
		redir(tmp_seq, &str_low, 2);
		printf("env: No such file or directory\n");
		return (127);
	}
	tmp = shell->env;
	while (tmp)
	{
		if (ft_strlen(tmp->key) == 1 & tmp->key[0] == '_')
			printf("%s=/usr/bin/env\n", tmp->key);
		else if (tmp->value)
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	redir(tmp_seq, &str_low, 2);
	return (0);
}

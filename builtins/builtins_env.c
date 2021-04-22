#include "../minibash.h"

int builtins_env(t_shell *shell, t_seq *tmp_seq)
{
	t_env *tmp;

	printf("%d\n", envp_set_value(shell->env, "_", ft_strdup("/usr/bin/env")));
	tmp = shell->env;
	while (tmp)
	{
		if (tmp->value)
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return (0);
}

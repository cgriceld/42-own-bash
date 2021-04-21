#include "../minibash.h"

int builtins_env(t_shell *shell, t_seq *tmp_seq)
{
	t_env *tmp;

	envp_set_value(shell->env, "_", ft_strdup("shell->env"));
	tmp = shell->env;
	while (tmp)
	{
		if (tmp->value)
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	//printf("\n");
	return (0);
}

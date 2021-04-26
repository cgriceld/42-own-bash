#include "../minibash.h"

int builtins_env(t_shell *shell)
{
	t_env *tmp;

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

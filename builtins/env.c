#include "../minibash.h"

int env(t_shell *shell)
{
	t_env *tmp;

	tmp = shell->env;
	while (tmp->next)
	{
		printf("%s:%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	printf("%s:%s", tmp->key, tmp->value);
	return (0);
}

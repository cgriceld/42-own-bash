#include "../minibash.h"

int builtins_unset_value(t_shell *shell)
{
	t_env *env;
	t_env *previous;
	t_env *this;
	int len;
	//параметр после парсинга
	char *param;
	param = "LOGNAME";

	env = shell->env;
	len = ft_strlen(param);
	while (ft_strncmp(env->key, param, len) != 0 && env->next)
	{
		previous = env;
		env = env->next;
	}
	if (ft_strncmp(env->key, param, len) != 0)
		return -1;
	this = env;
	previous->next = env->next;
	this->next = NULL;
	free(this);
	// понятьу что нет утечек
	return (0);
}

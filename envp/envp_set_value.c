#include "../minibash.h"

int envp_set_value(t_env *env, char *param, char *value)
{
	char *tmp;
	int len;

	len = ft_strlen(param);
	while (ft_strncmp(env->key, param, len) != 0 && env->next)
		env = env->next;
	if (ft_strncmp(env->key, param, len) != 0)
		return 1;
	tmp = env->value;
	env->value = ft_strdup(value);
	free(tmp);
	return 0;
}
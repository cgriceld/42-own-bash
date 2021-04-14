#include "../minibash.h"

int		put_the_value(t_env *env, char *buf, const char *param)
{
	char *tmp;
	int len;

	len = ft_strlen(param);
	while (ft_strncmp(env->key, param, len) != 0 && env->next)
		env = env->next;
	if (ft_strncmp(env->key, param, len) != 0)
		return -1;
	tmp = env->value;
	env->value = ft_strdup(buf);
	free(tmp);
	return 0;
}

char	*search_for_value(t_env *env, const char *param)
{
	int len;

	len = ft_strlen(param);
	while (ft_strncmp(env->key, param, len) != 0 && env->next)
		env = env->next;
	if (ft_strncmp(env->key, param, len) != 0)
		return NULL;
	return (env->value);
}

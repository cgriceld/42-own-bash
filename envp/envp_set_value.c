#include "../minibash.h"

int	envp_set_value(t_shell *shell, char *param, char *value)
{
	t_env		*env;
	char		*tmp;
	int			len;

	env = shell->env;
	len = ft_strlen(param);
	while (ft_strncmp(env->key, param, len) != 0 && env->next)
		env = env->next;
	if (ft_strncmp(env->key, param, len) != 0)
		return (1);
	tmp = env->value;
	env->value = ft_strdup(value);
	if (tmp)
		free(tmp);
	return (0);
}

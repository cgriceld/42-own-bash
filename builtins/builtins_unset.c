#include "../minibash.h"

int	builtins_unset_value(t_shell *shell, t_seq *tmp_seq)
{
	t_env	*env;
	t_env	*previous;
	t_env	*this;
	int		i;
	int		len;

	i = 1;
	while (tmp_seq->args[i] != 0)
	{
		len = ft_strlen(tmp_seq->args[i]);
		env = shell->env;
		while (ft_strncmp(env->key, tmp_seq->args[i], len) != 0 && env->next)
		{
			previous = env;
			env = env->next;
		}
		if (ft_strncmp(env->key, tmp_seq->args[i], len) != 0)
			continue ;
		this = env;
		previous->next = env->next;
		this->next = NULL;
		free(this);
		i++;
	}
	return (0);
}

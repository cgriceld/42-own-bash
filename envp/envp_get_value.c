#include "../minibash.h"

char	*envp_get_value(t_shell *shell, char *match)
{
	t_env	*tmp;
	size_t	len;

	tmp = shell->env;
	len = ft_strlen(match);
	while (tmp)
	{
		if ((ft_strlen(tmp->key) == len) && !ft_strncmp(tmp->key, match, len))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}
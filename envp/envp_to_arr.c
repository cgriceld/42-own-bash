#include "../minibash.h"

static void	free_arr(char ***arr, t_shell *shell, size_t i)
{
	ft_twodarr_free(arr, i);
	free_error(strerror(errno), &shell);
}

char	**envp_to_arr(t_shell *shell)
{
	char	**arr;
	t_env	*l_tmp;
	char	*s_tmp;
	size_t	i;

	arr = (char **)malloc(sizeof(char *) * (shell->env_size + 1));
	if (!arr)
		free_error(strerror(errno), &shell);
	arr[shell->env_size] = NULL;
	l_tmp = shell->env;
	i = 0;
	while (l_tmp)
	{
		s_tmp = ft_strjoin(l_tmp->key, "=");
		if (!s_tmp)
			free_arr(&arr, shell, i);
		arr[i] = ft_strjoin(s_tmp, l_tmp->value);
		free(s_tmp);
		if (!arr[i])
			free_arr(&arr, shell, i);
		l_tmp = l_tmp->next;
		i++;
	}
	return (arr);
}

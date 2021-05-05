#include "../minibash.h"

static void	envp_lstfill(char *envp, t_env *curr, t_shell *shell)
{
	char	*sep;
	char	*end;
	int		lvl;

	sep = ft_strchr(envp, '=');
	curr->key = ft_substr(envp, 0, sep - envp);
	if (!curr->key)
		free_error(strerror(errno), &shell);
	end = sep;
	while (*end)
		end++;
	sep++;
	if (!ft_strncmp(curr->key, "SHLVL", 5))
	{
		lvl = ft_atoi(sep);
		curr->value = ft_itoa(++lvl);
	}
	else
		curr->value = ft_substr(envp, sep - envp, end - sep);
	if (!curr->value)
		free_error(strerror(errno), &shell);
	curr->next = NULL;
	shell->env_size++;
}

void		envp_to_list(char **envp, t_shell *shell)
{
	t_env *tmp;

	shell->env = (t_env *)malloc(sizeof(t_env));
	if (!shell->env)
		free_error(strerror(errno), &shell);
	shell->env_size = 0;
	envp_lstfill(*envp, shell->env, shell);
	tmp = shell->env;
	envp++;
	while (*envp)
	{
		tmp->next = (t_env *)malloc(sizeof(t_env));
		tmp = tmp->next;
		if (!tmp)
			free_error(strerror(errno), &shell);
		envp_lstfill(*envp, tmp, shell);
		envp++;
	}
}
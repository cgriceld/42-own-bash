#include "../minibash.h"

int print_export(t_shell *shell)
{
	t_env *tmp;

	tmp = shell->env;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, "_", 2) != 0)
		{
			printf("declare -x %s", tmp->key);
			if (tmp->value)
				printf(" =\"%s\"", tmp->value);
			printf("\n");
		}
		tmp = tmp->next;
	}
	return (0);
}

int builtins_export(t_shell *shell)
{
	t_env *export;
	t_env *tmp;
	char **split;
	int count;

	//параметр после парсинга
	char *param;
	param = ft_strdup("LOGNAME=abc");
	//param = NULL;

	if (!param)
		print_export(shell);
	else
	{
		//надо учесть что может быть несколько значений и сделать цикл
		//как вариант сделать разделить по равно, но не сплитом 2 сплита или один
//		split = ft_split(param);
//		count = 0;
//		while (split[count] != NULL)
//			count ++;
//		if (count > 2)
//		{
//			while (count--)
//				free(split[count]);
//			free(split);
//			return (-1);
//		}


		if (envp_set_value(shell->env, param, value) == 0)
			return (0);
		export = (t_env *)malloc(sizeof(t_env));
		if (!export)
			free_error(strerror(errno), &shell);
		export->next = NULL;
		export->key = param;
		export->value = value;
		tmp = shell->env;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = export;
	}
	return (0);
}

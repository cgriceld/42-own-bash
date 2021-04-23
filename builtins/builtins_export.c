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

void pair_param_value(t_seq *tmp_seq, int i,  char **param, char **value)
{
	int n;
	int len;
	*value = NULL;
	*param = NULL;
	len = ft_strlen(tmp_seq->args[i]);
	n = 0;
	while (tmp_seq->args[i][n] != '=' && len > 0)
	{
		n++;
		len--;
	}
	if (len > 0)
	{
		tmp_seq->args[i][n] = 0;
		*value = ft_strdup(&(tmp_seq->args[i][n + 1]));
	}
	*param = ft_strdup(tmp_seq->args[i]);
}

int builtins_export(t_shell *shell, t_seq *tmp_seq)
{

	char *value;
	char *param;
	int len;
	int i;
	int n;

	if (tmp_seq->args[1] == 0)
		return (print_export(shell));
	i = 1;
	while (tmp_seq->args[i] != 0)
	{
		value = NULL;
		param = NULL;
		if (tmp_seq->args[i][0] == '=')
		{
			printf("export: `%s': not a valid identifier\n", tmp_seq->args[i]);
				return (1);
		}
//		len = ft_strlen(tmp_seq->args[i]);
//		n = 0;
//		while (tmp_seq->args[i][n] != '=' && len > 0)
//		{
//			n++;
//			len--;
//		}
//		if (len > 0)
//		{
//			tmp_seq->args[i][n] = 0;
//			value = ft_strdup(&(tmp_seq->args[i][n + 1]));
//		}
//		param = ft_strdup(tmp_seq->args[i]);
		pair_param_value(tmp_seq, i, &param, &value);
		if (value == NULL && envp_get_value(shell, param) != NULL)
		{
			i++;
			continue ;
		}
		if (envp_set_value(shell, param, value) == 0)
		{
			i++;
			continue ;
		}
		else
			envp_new_value(shell, param, value);
		i++;
	}
	return (0);
}

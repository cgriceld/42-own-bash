/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgriceld <cgriceld@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 13:39:09 by sbrenton          #+#    #+#             */
/*   Updated: 2021/05/13 12:47:35 by cgriceld         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

void	print_declations(t_list *key_sort, t_shell *shell)
{
	if (ft_strncmp((char *)key_sort->content, "_", 2) != 0)
	{
		printf("declare -x %s", (char *)(key_sort->content));
		if (envp_get_value(shell, key_sort->content) != NULL)
			printf(" =\"%s\"", envp_get_value(shell, key_sort->content));
		printf("\n");
	}
}

int	print_export(t_shell *shell)
{
	t_env		*tmp;
	t_list		*key_sort;
	t_list		*sort_start;

	sort_start = NULL;
	tmp = shell->env;
	while (tmp)
	{
		sort_start = put_to_sort_list(ft_strdup(tmp->key), sort_start);
		tmp = tmp->next;
	}
	key_sort = sort_start;
	while (key_sort)
	{
		if (((char *)key_sort->content)[0] < 'a'
		|| ((char *)key_sort->content)[0] > 'z')
			print_declations(key_sort, shell);
		key_sort = key_sort->next;
	}
	key_sort = sort_start;
	while (key_sort)
	{
		if (((char *)key_sort->content)[0] >= 'a'
		&& ((char *)key_sort->content)[0] <= 'z')
			print_declations(key_sort, shell);
		key_sort = key_sort->next;
	}
	ft_lstclear(&sort_start, free);
	return (0);
}

void	pair_param_value(t_seq *tmp_seq, int i,  char **param, char **value)
{
	int	n;
	int	len;

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

int	check_is_valid(t_seq *tmp_seq, int i)
{
	int	n;

	n = 0;
	if ((tmp_seq->args[i][0] == '_') ||
		(tmp_seq->args[i][0] >= 'a' && tmp_seq->args[i][0] <= 'z') ||
		(tmp_seq->args[i][0] >= 'A' && tmp_seq->args[i][0] <= 'Z'))
		n++;
	else
	{
		printf("export: `%s': not a valid identifier\n", tmp_seq->args[i]);
		return (2);
	}
	while (tmp_seq->args[i][n] != 0 && tmp_seq->args[i][n] != '=')
	{
		if ((tmp_seq->args[i][n] == '_') || (tmp_seq->args[i][n] == '\n') ||
			(tmp_seq->args[i][n] >= 'a' && tmp_seq->args[i][n] <= 'z') ||
			(tmp_seq->args[i][n] >= 'A' && tmp_seq->args[i][n] <= 'Z') ||
			(tmp_seq->args[i][n] >= '0' && tmp_seq->args[i][n] <= '9'))
			n++;
		else
		{
			printf("export: `%s': not a valid identifier\n", tmp_seq->args[i]);
			return (2);
		}
	}
	return (0);
}

int	builtins_export(t_shell *shell, t_seq *tmp_seq, char *str_low)
{

	char	*value;
	char	*param;
	int		i;

	if (redir(shell, tmp_seq, str_low, 0))
		return (2);
	str_low = NULL;
	if (tmp_seq->args[1] == 0 || tmp_seq->args[1][0] == '\n')
		return (print_export(shell));
	i = 1;
	while (tmp_seq->args[i] != 0)
	{
		value = NULL;
		param = NULL;
		if (check_is_valid(tmp_seq, i) == 2)
			return (2);
//		if ((tmp_seq->args[i][0] == '_') ||
//		(tmp_seq->args[i][0] >= 'a' && tmp_seq->args[i][0] <= 'z') ||
//		(tmp_seq->args[i][0] >= 'A' && tmp_seq->args[i][0] <= 'Z'))
//		{
//			printf("export: `%s': not a valid identifier\n", tmp_seq->args[i]);
//				return (1);
//		}
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
	redir(shell, tmp_seq, str_low, 2);
	return (0);
}

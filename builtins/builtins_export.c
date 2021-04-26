/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrenton <sbrenton@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 13:39:09 by sbrenton          #+#    #+#             */
/*   Updated: 2021/04/26 01:08:30 by lesia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

// поправить по норме!!!

int print_export(t_shell *shell)
{
	t_env *tmp;
	t_list *key_sort;
	t_list *sort_start;

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
		if (((char *)key_sort->content)[0] < 'a' || ((char *)key_sort->content)[0] > 'z')
		{
			if (ft_strncmp((char *)key_sort->content, "_", 2) != 0)
			{
				printf("declare -x %s", (char *)(key_sort->content));
				if (envp_get_value(shell, key_sort->content) != NULL)
					printf(" =\"%s\"", envp_get_value(shell, key_sort->content));
				printf("\n");
			}
		}
		key_sort = key_sort->next;
	}
	key_sort = sort_start;
	while (key_sort)
	{
		if (((char *)key_sort->content)[0] >= 'a' && ((char *)key_sort->content)[0] <= 'z')
		{
			if (ft_strncmp((char *)key_sort->content, "_", 2) != 0)
			{
				printf("declare -x %s", (char *)(key_sort->content));
				if (envp_get_value(shell, key_sort->content) != NULL)
					printf(" =\"%s\"", envp_get_value(shell, key_sort->content));
				printf("\n");
			}
		}
		key_sort = key_sort->next;
	}
	ft_lstclear(&sort_start, free);
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

	if (tmp_seq->args[1] == 0 || tmp_seq->args[1][0] == '\n')
		return (print_export(shell));
	i = 1;
	while (tmp_seq->args[i] != 0)
	{
		value = NULL;
		param = NULL;
		if (tmp_seq->args[i][0] == '=')
	//	(tmp_seq->args[i][0] >= 'а' && tmp_seq->args[i][0] <= 'я'))
		{
			printf("export: `%s': not a valid identifier\n", tmp_seq->args[i]);
				return (1);
		}
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

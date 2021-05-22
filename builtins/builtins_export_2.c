/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrenton <sbrenton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 13:39:09 by sbrenton          #+#    #+#             */
/*   Updated: 2021/05/22 09:00:03 by sbrenton         ###   ########.fr       */
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

int	print_export(t_shell *shell, t_list *key_sort, t_list *sort_start)
{
	t_env		*tmp;

	sort_start = NULL;
	tmp = shell->env;
	while (tmp)
	{
		sort_start = put_to_sort_list(ft_strdup(tmp->key), sort_start, NULL, NULL);
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

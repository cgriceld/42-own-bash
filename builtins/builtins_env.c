/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrenton <sbrenton@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 12:59:57 by sbrenton          #+#    #+#             */
/*   Updated: 2021/04/26 01:08:30 by lesia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

int builtins_env(t_shell *shell, t_seq *tmp_seq)
{
	t_env *tmp;

	if (envp_get_value(shell, "PATH") == NULL)
	{
		printf("env: No such file or directory\n");
		return (127);
	}
	tmp = shell->env;
	while (tmp)
	{
		if (ft_strlen(tmp->key) == 1 & tmp->key[0] == '_')
			printf("%s=/usr/bin/env\n", tmp->key);
		else if (tmp->value)
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return (0);
}

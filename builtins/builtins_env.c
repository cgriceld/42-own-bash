/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrenton <sbrenton@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 12:59:57 by sbrenton          #+#    #+#             */
/*   Updated: 2021/05/10 18:25:46 by sbrenton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

int	builtins_env(t_shell *shell, t_seq *tmp_seq, char *str_low)
{
	t_env	*tmp;
	int		fds[2];

	fds[0] = dup(0);
	fds[1] = dup(1);
	run_redirect(tmp_seq, shell);
	free(str_low);
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
	dup2(fds[1], 1);
	return (0);
}

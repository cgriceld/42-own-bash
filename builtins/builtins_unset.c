/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrenton <sbrenton@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 13:38:46 by sbrenton          #+#    #+#             */
/*   Updated: 2021/04/26 08:03:01 by lesia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

// а если первая в списке? .проверить

int	builtins_unset_value(t_shell *shell, t_seq *tmp_seq)
{
	t_env	*env;
	t_env	*previous;
	t_env	*this;
	int		i;
	int		len;

	i = 1;
	while (tmp_seq->args[i] != 0)
	{
		len = ft_strlen(tmp_seq->args[i]);
		env = shell->env;
		if (ft_strncmp(env->key, tmp_seq->args[i], len) == 0)
		{
			this = env;
			shell->env = env->next;
			free(this);
			i++;
			continue;
		}
		while (ft_strncmp(env->key, tmp_seq->args[i], len) != 0 && env->next)
		{
			previous = env;
			env = env->next;
		}
		if (ft_strncmp(env->key, tmp_seq->args[i], len) != 0)
		{
			i++;
			continue;
		}
		this = env;
		previous->next = env->next;
		this->next = NULL;
		free(this);
		i++;
	}
	return (0);
}

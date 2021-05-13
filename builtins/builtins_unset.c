/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgriceld <cgriceld@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 13:38:46 by sbrenton          #+#    #+#             */
/*   Updated: 2021/05/12 12:29:36 by cgriceld         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../Downloads/42-own-bash-main/minibash.h"

// int	static first_value(t_shell *shell, t_seq *tmp_seq, char *str_low)
// {
// //			this = env;
// //			shell->env = env->next;
// //			free(this);
// //			*i += 1;

// }

int	builtins_unset_value(t_shell *shell, t_seq *tmp_seq, char *str_low)
{
	t_env	*env;
	t_env	*previous;
	t_env	*this;
	int		*i;
	int		len;

	if (redir(shell, tmp_seq, str_low, 1))
		return (2);
	*i = 1;
	while (tmp_seq->args[*i] != 0)
	{
		len = ft_strlen(tmp_seq->args[*i]);
		env = shell->env;
		if (ft_strncmp(env->key, tmp_seq->args[*i], len) == 0)
		{
			this = env;
			shell->env = env->next;
			free(this);
			*i += 1;
			continue;
		}
		while (ft_strncmp(env->key, tmp_seq->args[*i], len) != 0 && env->next)
		{
			previous = env;
			env = env->next;
		}
		if (ft_strncmp(env->key, tmp_seq->args[*i], len) != 0)
		{
			*i += 1;
			continue;
		}
		this = env;
		previous->next = env->next;
		this->next = NULL;
		free(this);
		*i += 1;
	}
	return (0);
}

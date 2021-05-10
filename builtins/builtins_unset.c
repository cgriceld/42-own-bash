/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrenton <sbrenton@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 13:38:46 by sbrenton          #+#    #+#             */
/*   Updated: 2021/05/10 19:38:26 by sbrenton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

int	static	unset_value( t_shell *shell, t_env	*env, int i)
{
	t_env	*this;

	this = env;
	shell->env = env->next;
	free(this->key);
	free(this->value);
	this->next = NULL;
	free(this);
	i += 1;
	return (i);
}

int	static	unset_last( t_env *previous, t_env	*env, int i)
{
	t_env	*this;

	this = env;
	previous->next = env->next;
	free(this->key);
	free(this->value);
	this->next = NULL;
	free(this);
	i += 1;
	return (i);
}

//убрать 6 строк еще
int	builtins_unset_value(t_shell *shell, t_seq *tmp_seq, char *str_low)
{
	t_env	*env;
	t_env	*previous;
	int		i;
	int		len;

	redir(shell, tmp_seq, str_low);
	i = 1;
	while (tmp_seq->args[i] != 0)
	{
		len = ft_strlen(tmp_seq->args[i]);
		env = shell->env;
		if (ft_strncmp(env->key, tmp_seq->args[i], len) == 0)
		{
			i = unset_value(shell, env, i);
			continue ;
		}
		while (ft_strncmp(env->key, tmp_seq->args[i], len) != 0 && env->next)
		{
			previous = env;
			env = env->next;
		}
		if (ft_strncmp(env->key, tmp_seq->args[i], len) != 0)
		{
			i += 1;
			continue ;
		}
		i = unset_last(previous, env, i);
	}
	return (0);
}

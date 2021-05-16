/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_set_value.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgriceld <cgriceld@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 22:39:21 by sbrenton          #+#    #+#             */
/*   Updated: 2021/05/16 17:55:54 by sbrenton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

int	envp_set_value(t_shell *shell, char *param, char *value)
{
	t_env		*env;
	char		*tmp;
	int			len;

	env = shell->env;
	len = ft_strlen(param);
	while (ft_strncmp(env->key, param, len) != 0 && env->next)
		env = env->next;
	if (ft_strncmp(env->key, param, len) != 0)
		return (1);
	tmp = env->value;
	env->value = ft_strdup(value);
	if (tmp)
		free(tmp);
	return (0);
}

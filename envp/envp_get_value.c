/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_get_value.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgriceld <cgriceld@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 22:39:21 by sbrenton          #+#    #+#             */
/*   Updated: 2021/05/16 16:40:26 by sbrenton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

char	*envp_get_value(t_shell *shell, char *match)
{
	t_env	*tmp;
	size_t	len;

	tmp = shell->env;
	len = ft_strlen(match);
	while (tmp)
	{
		if ((ft_strlen(tmp->key) == len) && !ft_strncmp(tmp->key, match, len))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

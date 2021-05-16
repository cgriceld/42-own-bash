/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_new_value.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgriceld <cgriceld@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 22:39:21 by sbrenton          #+#    #+#             */
/*   Updated: 2021/05/16 17:55:54 by sbrenton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

int	envp_new_value(t_shell *shell, char *param, char *value)
{
	t_env	*export;
	t_env	*tmp;

	export = (t_env *)malloc(sizeof(t_env));
	if (!export)
		free_error(strerror(errno), &shell);
	export->next = NULL;
	export->key = param;
	export->value = value;
	tmp = shell->env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = export;
	shell->env_size++;
	return (0);
}

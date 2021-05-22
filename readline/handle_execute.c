/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_execute.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgriceld <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 13:57:59 by cgriceld          #+#    #+#             */
/*   Updated: 2021/05/22 13:58:01 by cgriceld         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

void	handle_execute(t_shell *shell)
{
	char	*tmp;

	printf("\n");
	if (shell->hist_ptr != shell->hist_curr)
	{
		tmp = shell->hist_curr->command;
		shell->hist_curr->command = ft_strdup(shell->hist_ptr->command);
		free(tmp);
		shell->hist_curr->len = shell->hist_ptr->len;
		if (shell->hist_ptr->cache)
			deal_cache(shell);
	}
	if (shell->hist_curr->len)
	{
		parser(shell);
		shell->hist_curr->next = (t_history *)malloc(sizeof(t_history));
		if (!shell->hist_curr->next)
			free_error(strerror(errno), &shell);
		shell->hist_curr->next->prev = shell->hist_curr;
		shell->hist_curr = shell->hist_curr->next;
		init_hist(shell);
	}
	shell->hist_ptr = shell->hist_curr;
}

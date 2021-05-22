/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry_point.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgriceld <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 14:02:24 by cgriceld          #+#    #+#             */
/*   Updated: 2021/05/22 14:02:29 by cgriceld         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minibash.h"

static void	prepare(int argc, t_shell **shell)
{
	if (argc != 1)
		lite_error(WRONG_ARGS);
	*shell = (t_shell *)malloc(sizeof(t_shell));
	if (!*shell)
		lite_error(strerror(errno));
	(*shell)->env = NULL;
	(*shell)->seq = NULL;
	(*shell)->history = (t_history *)malloc(sizeof(t_history));
	if (!(*shell)->history)
		free_error(strerror(errno), shell);
	(*shell)->history->prev = NULL;
	(*shell)->hist_curr = (*shell)->history;
	(*shell)->hist_ptr = (*shell)->hist_curr;
	init_hist(*shell);
	g_ret_status = 0;
}

int	main(int argc, char __attribute__((unused)) **argv, char **envp)
{
	t_shell	*shell;

	tgetent(NULL, getenv("TERM"));
	g_ret_status = 0;
	prepare(argc, &shell);
	envp_to_list(envp, shell);
	set_signals();
	ft_readline(shell, 0);
	free_error(NULL, &shell);
	return (g_ret_status);
}

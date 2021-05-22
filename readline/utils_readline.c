/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_readline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgriceld <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 13:59:05 by cgriceld          #+#    #+#             */
/*   Updated: 2021/05/22 13:59:07 by cgriceld         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

void	set_mode(int type)
{
	struct termios	term;

	tcgetattr(0, &term);
	if (!type)
		term.c_lflag &= ~(ECHO | ICANON);
	else
		term.c_lflag |= (ECHO | ICANON);
	tcsetattr(0, TCSANOW, &term);
}

void	prompt(void)
{
	write(1, PROMPT, ft_strlen(PROMPT));
}

void	init_hist(t_shell *shell)
{
	shell->hist_curr->command = ft_strdup("");
	if (!shell->hist_curr->command)
		free_error(strerror(errno), &shell);
	shell->hist_curr->cache = NULL;
	shell->hist_curr->len = 0;
	shell->hist_curr->cache_len = 0;
	shell->hist_curr->next = NULL;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgriceld <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 13:53:42 by cgriceld          #+#    #+#             */
/*   Updated: 2021/05/22 13:53:45 by cgriceld         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

void	dollar_path(t_redir_chain *tmp_redir, t_shell *shell, t_quo *quo)
{
	char	*start;

	start = quo->end;
	if (*start == ' ')
		start--;
	while (*start != ' ' && *start != '>' && *start != '<')
		start--;
	start++;
	tmp_redir->path = ft_substr(start, 0, quo->end - start);
	if (!tmp_redir->path)
		error_quotes(&quo, &shell);
}

void	parse_input(t_redir_chain *tmp_redir, t_shell *shell, t_quo *quo)
{
	if (!tmp_redir->path && (tmp_redir->type & AMBIGUOUS))
		dollar_path(tmp_redir, shell, quo);
	else if (!tmp_redir->path)
		syntax_error(shell, '<');
	tmp_redir->type |= REDIR_IN;
}

void	parse_output(t_redir_chain *tmp_redir, t_shell *shell, t_quo *quo)
{
	if (!tmp_redir->path && (tmp_redir->type & AMBIGUOUS))
		dollar_path(tmp_redir, shell, quo);
	else if (!tmp_redir->path)
		syntax_error(shell, '>');
	if (!(tmp_redir->type & REDIR_APPEND))
		tmp_redir->type |= REDIR_OUT;
}

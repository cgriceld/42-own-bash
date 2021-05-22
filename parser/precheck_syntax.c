/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precheck_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgriceld <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 13:55:50 by cgriceld          #+#    #+#             */
/*   Updated: 2021/05/22 13:55:53 by cgriceld         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minibash.h"

static void	manage_quotes(char *str, unsigned char *f, t_shell *shell)
{
	if (*str == '"')
	{
		if ((*f & DOUBLED) && !(*f & SINGLE) && \
			even_escaped(shell->hist_curr->command, str))
			*f &= ~DOUBLED;
		else if (!(*f & SINGLE) && !(*f & DOUBLED) && \
				even_escaped(shell->hist_curr->command, str))
			*f |= DOUBLED;
	}
	else if (*str == '\'')
	{
		if ((*f & SINGLE) && !(*f & DOUBLED))
			*f &= ~SINGLE;
		else if (!(*f & SINGLE) && !(*f & DOUBLED) && \
				even_escaped(shell->hist_curr->command, str))
			*f |= SINGLE;
	}
}

static void	manage_separator(t_shell *shell, char **start, char *str, char sym)
{
	char			*tmp;
	char			*tmp2;
	char			*after;
	char			*before;
	static size_t	len = 0;

	manage_before(&before, shell, len);
	tmp2 = ft_substr(shell->hist_curr->command, \
			*start - shell->hist_curr->command, str - *start);
	after = ft_strjoin_sym(tmp2, str, sym);
	free(tmp2);
	tmp = shell->seq->run;
	shell->seq->run = ft_strjoin(before, after);
	free(tmp);
	free(before);
	free(after);
	if (!shell->seq->run)
		free_error(strerror(errno), &shell);
	len = len + (str - *start) + 2;
	*start = str + 1;
	if (sym == ' ' && *str == ';')
		shell->sep[0]++;
	if (sym == ' ' && *str == '|')
		shell->sep[1]++;
}

static void	quo_syntax_utils(char *str, t_shell *shell)
{
	if (*str == ';')
		shell->sep[0]++;
	else if (*str == '|')
		shell->sep[1]++;
}

static int	quo_syntax(char *str, unsigned char f, t_shell *shell, char *start)
{
	while (*str)
	{
		if (*str == '"' || *str == '\'')
			manage_quotes(str, &f, shell);
		else if (*str == ';' || *str == '|')
		{
			if (*str == '|' && !(f & DOUBLED) && !(f & SINGLE) && \
				*(str - 1) == '>')
			{
				if (!even_escaped(shell->hist_curr->command, (str - 1)))
					shell->sep[1]++;
			}
			else if (!(f & DOUBLED) && !(f & SINGLE) && *(str - 1) == '\\')
			{
				if (even_escaped(shell->hist_curr->command, str))
					manage_separator(shell, &start, str, ' ');
			}
			else if ((f & SINGLE) || (f & DOUBLED))
				manage_separator(shell, &start, str, '\\');
			else
				quo_syntax_utils(str, shell);
		}
		str++;
	}
	return (quo_syntax_return(f));
}

int	precheck_syntax(t_shell *shell)
{
	int				res;
	unsigned char	f;
	char			*start;

	if (ft_strchrset(shell->hist_curr->command, "'\";|"))
	{
		shell->seq->info |= QUOTED;
		shell->sep[0] = 0;
		shell->sep[1] = 0;
		f = ZERO;
		start = shell->hist_curr->command;
		res = quo_syntax(shell->hist_curr->command, f, shell, start);
		if (!res)
			return (0);
		if (res == 1)
			syntax_error(shell, '"');
		else if (res == 2)
			syntax_error(shell, '\'');
		free_seq(&shell->seq);
		return (1);
	}
	return (0);
}

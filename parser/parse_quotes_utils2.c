#include "../minibash.h"

static void	parse_singleq_utils(t_seq *tmp_seq, t_shell *shell, t_quo *quo, \
					t_quo_split *tmp_split)
{
	if (*(quo->end + 1) == '|' || *(quo->end + 1) == ';')
		parse_escape(tmp_seq, shell, quo, tmp_split);
	else
		join_one_sym(shell, quo, &tmp_split->arg, "\\");
}

void	parse_singleq(t_seq *tmp_seq, t_shell *shell, t_quo *quo, \
					t_quo_split *tmp_split)
{
	quo->end++;
	quo->start++;
	while (*quo->end)
	{
		quo->start = quo->end;
		while (*quo->end && !ft_strchr("\'\\", *quo->end))
			quo->end++;
		join_routine(tmp_seq, shell, quo, tmp_split);
		if (tmp_split && tmp_split->next)
			tmp_split = tmp_split->next;
		if (*quo->end == '\'')
			break ;
		else if (*quo->end == '\\')
		{
			parse_singleq_utils(tmp_seq, shell, quo, tmp_split);
			if (tmp_split && tmp_split->next)
				tmp_split = tmp_split->next;
		}
		else
			quo->end++;
	}
	quo->end++;
}

void	parse_escape(t_seq *tmp_seq, t_shell *shell, t_quo *quo, \
					t_quo_split *tmp_split)
{
	while (*quo->end == '\\')
	{
		quo->slashes++;
		quo->end++;
	}
	join_routine(tmp_seq, shell, quo, tmp_split);
	quo->slashes = 0;
}

static void	parse_doubleq_utils(t_seq *tmp_seq, t_shell *shell, t_quo *quo, \
					t_quo_split *tmp_split)
{
	if (*quo->end == '\\' && ft_strchr("\\$\"|;", *(quo->end + 1)))
		parse_escape(tmp_seq, shell, quo, tmp_split);
	else if (*quo->end == '$' && *(quo->end + 1) != '"')
		parse_dollar(tmp_seq, shell, quo, tmp_split);
	else
	{
		quo->end++;
		join_routine(tmp_seq, shell, quo, tmp_split);
	}
}

void	parse_doubleq(t_seq *tmp_seq, t_shell *shell, t_quo *quo, \
					t_quo_split *tmp_split)
{
	quo->end++;
	quo->start++;
	while (*quo->end)
	{
		quo->start = quo->end;
		while (*quo->end && !ft_strchr("$\"\\", *quo->end))
			quo->end++;
		if (ft_strchr("$\"", *quo->end) && \
					cancel_escape(tmp_seq, shell, quo, tmp_split))
			continue ;
		join_routine(tmp_seq, shell, quo, tmp_split);
		if (tmp_split && tmp_split->next)
			tmp_split = tmp_split->next;
		if (*quo->end == '"')
			break ;
		parse_doubleq_utils(tmp_seq, shell, quo, tmp_split);
		if (tmp_split && tmp_split->next)
			tmp_split = tmp_split->next;
	}
	quo->end++;
}

#include "../minibash.h"

// if already check close match, no check for \0 ?
void parse_singleq(t_seq *tmp_seq, t_shell *shell, t_quo *quo, t_quo_split *tmp_split)
{
	quo->end++;
	while (*quo->end && *quo->end != '\'')
		quo->end++;
	if (*quo->end == '\'' && tmp_split)
		join_args(tmp_seq, shell, quo, tmp_split);
	else
		join_args2(tmp_seq, shell, quo, &tmp_seq->tmp_redir->path);
	quo->end++;
}

// check for end?
void parse_escape(t_seq *tmp_seq, t_shell *shell, t_quo *quo, t_quo_split *tmp_split)
{
	int num;

	num = 0;
	while (*quo->end == '\\')
	{
		num++;
		quo->end++;
	}
	if (!(num % 2))
	{
		quo->slashes = num / 2;
		quo->last_slash = 0;
	}
	else
	{
		quo->slashes = num / 2 + 1;
		quo->last_slash = 1;
	}
	if (tmp_split)
		join_args(tmp_seq, shell, quo, tmp_split);
	else
		join_args2(tmp_seq, shell, quo, &tmp_seq->tmp_redir->path);
	quo->slashes = 0;
	quo->start = quo->end;
}

// start bound with slash
// FIX slash !!! + if not $
void parse_doubleq(t_seq *tmp_seq, t_shell *shell, t_quo *quo, t_quo_split *tmp_split)
{
	quo->end++;
	while (*quo->end)
	{
		quo->start = quo->end;
		while (*quo->end && !ft_strchr("$\"\\", *quo->end))
			quo->end++;
		if (ft_strchr("$\"", *quo->end) && cancel_escape(tmp_seq, shell, quo, tmp_split))
			continue;
		join_routine(tmp_seq, shell, quo, tmp_split);
		if (tmp_split && tmp_split->next)
			tmp_split = tmp_split->next;
		if (*quo->end == '\\')
		{
			if (*(quo->end + 1) == '\\' || *(quo->end + 1) == '$' || *(quo->end + 1) == '"')
				parse_escape(tmp_seq, shell, quo, tmp_split);
			else
			{
				quo->end++;
				join_routine(tmp_seq, shell, quo, tmp_split);
			}
		}
		else if (*quo->end == '$')
		{
			if (*(quo->end + 1) != '"')
				parse_dollar(tmp_seq, shell, quo, tmp_split);
			else
			{
				quo->end++;
				join_routine(tmp_seq, shell, quo, tmp_split);
			}
		}
		else if (*quo->end == '"')
		{
			quo->end++;
			break;
		}
		if (tmp_split && tmp_split->next)
			tmp_split = tmp_split->next;
	}
}
		// if ((*quo->end == '\\' && *(quo->end + 1) == '\\') || *quo->end == '$')
		// {
		// 	join_routine(tmp_seq, shell, quo, tmp_split);
		// 	if (tmp_split->next)
		// 		tmp_split = tmp_split->next;
		// 	if (*quo->end == '\\')
		// 		parse_escape(tmp_seq, shell, quo, tmp_split);
		// 	else if (*quo->end == '$')
		// 		parse_dollar(tmp_seq, shell, quo, tmp_split);
		// 	continue;
		// }
		// if (*quo->end == '"')
		// {
		// 	if (*(quo->end - 1) == '\\' && quo->last_slash)
		// 		join_one_sym(shell, quo, &tmp_split->arg, "\"");
		// 	else
		// 	{
		// 		if (tmp_split)
		// 			join_args(tmp_seq, shell, quo, tmp_split);
		// 		else
		// 			join_args2(tmp_seq, shell, quo, &tmp_seq->tmp_redir->path);
		// 		quo->end++;
		// 		break;
		// 	}
		// }
		// quo->end++;

#include "../minibash.h"

// if already check close match, no check for \0 ?
void parse_singleq(t_seq *tmp_seq, t_shell *shell, t_quo *quo, t_quo_split *tmp_split)
{
	quo->end++;
	while (*quo->end && *quo->end != '\'')
		quo->end++;
	if (*quo->end == '\'')
		join_args(tmp_seq, shell, quo, tmp_split);
	// if (tmp_split->next)
	// 	tmp_split = tmp_split->next;
	// quo->after_space = 0;
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
	join_args(tmp_seq, shell, quo, tmp_split);
	quo->slashes = 0;
	// if (tmp_split->next)
	// 	tmp_split = tmp_split->next;
	// quo->after_space = 0;
	quo->start = quo->end;
}

// start bound with slash
void parse_doubleq(t_seq *tmp_seq, t_shell *shell, t_quo *quo, t_quo_split *tmp_split)
{
	quo->end++;
	while (*quo->end)
	{
		if (*quo->end == '\\')
		{
			join_routine(tmp_seq, shell, quo, tmp_split);
			parse_escape(tmp_seq, shell, quo, tmp_split);
		}
		if (*quo->end == '"')
		{
			if (*(quo->end - 1) == '\\' && quo->last_slash)
				quo->last_slash = 0;
			else
			{
				join_args(tmp_seq, shell, quo, tmp_split);
				// if (tmp_split->next)
				// 	tmp_split = tmp_split->next;
				// quo->after_space = 0;
				quo->end++;
				break;
			}
		}
		quo->end++;
	}
}
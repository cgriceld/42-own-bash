#include "../minibash.h"

static void join_args(t_seq *tmp_seq, t_shell *shell, t_quo *quo, t_quo_split *tmp_split)
{
	char *tmp;

	if (quo->after_space && tmp_split->arg && !init_quo_split(&tmp_split->next))
	{
		tmp_split->next->arg = ft_strtrim(ft_substr(\
		tmp_seq->run, quo->start - tmp_seq->run, quo->end - quo->start), "'\"");
	}
	else if (!quo->after_space)
	{
		tmp = tmp_split->arg;
		tmp_split->arg = ft_strjoin(tmp_split->arg, ft_strtrim(ft_substr(\
		tmp_seq->run, quo->start - tmp_seq->run, quo->end - quo->start), "'\""));
		free(tmp);
	}
	else if (quo->after_space && !tmp_split->arg)
	{
		tmp_split->arg = ft_strtrim(ft_substr(\
		tmp_seq->run, quo->start - tmp_seq->run, quo->end - quo->start), "'\"");
	}
}

static void parse_singleq(t_seq *tmp_seq, t_shell *shell, t_quo *quo, t_quo_split *tmp_split)
{
	char *tmp;

	while (*quo->end && *quo->end != '\'')
		quo->end++;
	if (*quo->end == '\'')
		join_args(tmp_seq, shell, quo, tmp_split);
	quo->end++;
}

static void find_quotes(t_seq *tmp_seq, t_shell *shell, t_quo *quo, t_quo_split *tmp_split)
{
	while (*quo->end)
	{
		while (*quo->end && *quo->end == ' ')
			quo->end++;
		quo->start = quo->end;
		while (*quo->end && *quo->end != ' ' && *quo->end != '\'')
			quo->end++;
		if (*quo->end == ' ' || !*quo->end)
		{
			if (*quo->end == ' ')
				quo->after_space = 1;
			join_args(tmp_seq, shell, quo, tmp_split);
		}
		else if (*quo->end == '\'')
		{
			quo->end++;
			parse_singleq(tmp_seq, shell, quo, tmp_split);
			quo->after_space = 0;
		}
		if (tmp_split->next)
		{
			tmp_split = tmp_split->next;
			quo->split_len++;
		}
	}
}

void parse_quotes(t_seq *tmp_seq, t_shell *shell)
{
	t_quo		*quo;
	t_quo_split	*tmp_split;

	if (!tmp_seq->run)
		tmp_seq->run = ft_strtrim(shell->hist_curr->command, " ");
	if (!tmp_seq->run)
		free_error(strerror(errno), &shell);
	quo = (t_quo *)malloc(sizeof(t_quo));
	if (!quo)
		free_error(strerror(errno), &shell);
	if (init_quo_split(&quo->split))
		error_quotes(&quo, &shell);
	quo->single_q = 0;
	quo->double_q = 0;
	quo->after_space = 1;
	quo->split_len = 1;
	tmp_split = quo->split;
	quo->end = tmp_seq->run;
	find_quotes(tmp_seq, shell, quo, tmp_split);
	fill_after_quotes(tmp_seq, shell, quo);
	free_quotes(&quo);
}

// free on errors
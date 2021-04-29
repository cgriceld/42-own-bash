#include "../minibash.h"

static void find_loop(t_seq *tmp_seq, t_shell *shell, t_quo *quo, t_quo_split *tmp_split)
{
	if (*quo->end == ' ')
	{
		if (*(quo->end - 1) == '\\' && quo->last_slash)
			join_one_sym(shell, quo, tmp_split, " ");
		else
			quo->after_space = 1;
	}
	while (*quo->end && *quo->end == ' ')
		quo->end++;
	quo->start = quo->end;
	while (*quo->end && !ft_strchr(" <>\"\\'", *quo->end))
		quo->end++;
	if (*quo->end == ' ' || !*quo->end)
	{
		join_args(tmp_seq, shell, quo, tmp_split);
		quo->after_space = 1;
	}
}

// check for start string bound when slash
static int cancel_escape(t_shell *shell, t_quo *quo, t_quo_split *tmp_split)
{
	if (*(quo->end - 1) == '\\' && quo->last_slash)
	{
		if (*quo->end == '>')
			join_one_sym(shell, quo, tmp_split, ">");
		if (*quo->end == '<')
			join_one_sym(shell, quo, tmp_split, "<");
		if (*quo->end == '"')
			join_one_sym(shell, quo, tmp_split, "\"");
		if (*quo->end == '\'')
			join_one_sym(shell, quo, tmp_split, "'");
		return (1);
	}
	return (0);
}

static void what_parse(t_seq *tmp_seq, t_shell *shell, t_quo *quo, t_quo_split *tmp_split)
{
	if (*quo->end == '\\')
		parse_escape(tmp_seq, shell, quo, tmp_split);
	else if (*quo->end == '\'')
		parse_singleq(tmp_seq, shell, quo, tmp_split);
	else if (*quo->end == '"')
		parse_doubleq(tmp_seq, shell, quo, tmp_split);
	else if (*quo->end == '>' || *quo->end == '<')
		parse_redirect(tmp_seq, shell, quo, tmp_split);
}

static void find_quotes(t_seq *tmp_seq, t_shell *shell, t_quo *quo, t_quo_split *tmp_split)
{
	while (*quo->end)
	{
		find_loop(tmp_seq, shell, quo, tmp_split);
		if (*quo->end && ft_strchr("<>\"\\'", *quo->end))
		{
			if (ft_strchr("<>\"'", *quo->end) && cancel_escape(shell, quo, tmp_split))
				continue;
			join_routine(tmp_seq, shell, quo, tmp_split);
			if (tmp_split->next)
				tmp_split = tmp_split->next;
			what_parse(tmp_seq, shell, quo, tmp_split);
			while (tmp_split->next)
				tmp_split = tmp_split->next;
			continue;
		}
		while (tmp_split->next)
			tmp_split = tmp_split->next;
		if (*quo->end)
			quo->end++;
	}
}

void parse_quotes(t_seq *tmp_seq, t_shell *shell)
{
	t_quo		*quo;
	t_quo_split	*tmp_split;

	if (!tmp_seq->run)
		tmp_seq->run = ft_strdup(shell->hist_curr->command);
	if (!tmp_seq->run)
		free_error(strerror(errno), &shell);
	quo = (t_quo *)malloc(sizeof(t_quo));
	if (!quo)
		free_error(strerror(errno), &shell);
	if (init_quo_split(&quo->split))
		error_quotes(&quo, &shell);
	quo->flag = ZERO;
	quo->after_space = 0;
	quo->split_len = 0;
	tmp_split = quo->split;
	quo->end = tmp_seq->run;
	quo->last_slash = 0;
	quo->slashes = 0;
	find_quotes(tmp_seq, shell, quo, tmp_split);
	fill_after_quotes(tmp_seq, shell, quo);
	free_quotes(&quo);
}

// free on errors
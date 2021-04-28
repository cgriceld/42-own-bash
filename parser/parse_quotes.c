#include "../minibash.h"

static void join_args(t_seq *tmp_seq, t_shell *shell, t_quo *quo, t_quo_split *tmp_split)
{
	char *tmp;

	if (quo->after_space && tmp_split->arg && !init_quo_split(&tmp_split->next))
	{
		if (quo->slashes)
			tmp_split->next->arg = ft_genstr('\\', quo->slashes);
		else
			tmp_split->next->arg = ft_strtrim(ft_substr(\
			tmp_seq->run, quo->start - tmp_seq->run, quo->end - quo->start), "'\"");
	}
	else if (!quo->after_space)
	{
		tmp = tmp_split->arg;
		if (quo->slashes)
		{
			if (quo->slashes == 1)
				quo->slashes = 0;
			tmp_split->arg = ft_strjoin(tmp_split->arg, ft_genstr('\\', quo->slashes));
		}
		else
			tmp_split->arg = ft_strjoin(tmp_split->arg, ft_strtrim(ft_substr(\
			tmp_seq->run, quo->start - tmp_seq->run, quo->end - quo->start), "'\""));
		free(tmp);
	}
	else if (quo->after_space && !tmp_split->arg)
	{
		if (quo->slashes)
			tmp_split->arg = ft_genstr('\\', quo->slashes);
		else
			tmp_split->arg = ft_strtrim(ft_substr(\
			tmp_seq->run, quo->start - tmp_seq->run, quo->end - quo->start), "'\"");
	}
}

// if already check close match, no check for \0 ?
static void parse_singleq(t_seq *tmp_seq, t_shell *shell, t_quo *quo, t_quo_split *tmp_split)
{
	char *tmp;

	quo->end++;
	while (*quo->end && *quo->end != '\'')
		quo->end++;
	if (*quo->end == '\'')
		join_args(tmp_seq, shell, quo, tmp_split);
	if (tmp_split->next)
		tmp_split = tmp_split->next;
	quo->after_space = 0;
	quo->end++;
	// if (*quo->end == ' ')
	// 	quo->after_space = 1;
}

static void even_escape(t_seq *tmp_seq, t_shell *shell, t_quo *quo, t_quo_split *tmp_split)
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
	if (tmp_split->next)
		tmp_split = tmp_split->next;
	quo->after_space = 0;
}

// check for end
static void parse_escape(t_seq *tmp_seq, t_shell *shell, t_quo *quo, t_quo_split *tmp_split)
{
	even_escape(tmp_seq, shell, quo, tmp_split);
	while (*quo->end == '\\')
		quo->end++;
	quo->start = quo->end;
	// while (*quo->end && !ft_strchr(" \\'", *quo->end))
	// 	quo->end++;
	// if (*quo->end == '\'' && !quo->last_slash)
	// {
	// 	// join_args(tmp_seq, shell, quo, tmp_split);
	// 	// if (tmp_split->next)
	// 	// 	tmp_split = tmp_split->next;
	// 	// quo->after_space = 0;
	// 	// quo->start = quo->end;
	// 	parse_singleq(tmp_seq, shell, quo, tmp_split);
	// }
	// else if (*quo->end == ' ')
	// {
	// 	//join_args(tmp_seq, shell, quo, tmp_split);
	// 	quo->after_space = 1;
	// }
}

static void find_quotes(t_seq *tmp_seq, t_shell *shell, t_quo *quo, t_quo_split *tmp_split)
{
	while (*quo->end)
	{
		if (*quo->end == ' ')
			quo->after_space = 1;
		while (*quo->end && *quo->end == ' ')
			quo->end++;
		quo->start = quo->end;
		while (*quo->end && !ft_strchr(" >\"\\'", *quo->end))
			quo->end++;
		if (*quo->end == ' ' || !*quo->end)
		{
			// if (*quo->end == ' ')
			// 	quo->after_space = 1;
			join_args(tmp_seq, shell, quo, tmp_split);
			quo->after_space = 1;
		}
		else if (*quo->end == '\\' || *quo->end == '\'')
		{
			if (*quo->end == '\'' && *(quo->end - 1) == '\\' && quo->last_slash)
			{
				quo->last_slash = 0;
				quo->end++;
				continue;
			}
			if (quo->start != quo->end)
			{
				join_args(tmp_seq, shell, quo, tmp_split);
				if (tmp_split->next)
					tmp_split = tmp_split->next;
				quo->after_space = 0;
				quo->start = quo->end;
			}
			if (*quo->end == '\\')
				parse_escape(tmp_seq, shell, quo, tmp_split);
			else if (*quo->end == '\'')
				parse_singleq(tmp_seq, shell, quo, tmp_split);
			while (tmp_split->next)
			{
				tmp_split = tmp_split->next;
				quo->split_len++;
			}
			continue;
		}
		while (tmp_split->next)
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
	quo->flag = ZERO;
	quo->after_space = 1;
	quo->split_len = 1;
	tmp_split = quo->split;
	quo->end = tmp_seq->run;
	quo->last_slash = 0;
	quo->slashes = 0;
	find_quotes(tmp_seq, shell, quo, tmp_split);
	fill_after_quotes(tmp_seq, shell, quo);
	free_quotes(&quo);
}

// free on errors
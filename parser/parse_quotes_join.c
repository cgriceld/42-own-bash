#include "../minibash.h"

void	join_args2(t_seq *tmp_seq, t_shell *shell, t_quo *quo, char **arg)
{
	char	*tmp;
	char	*tmp2;

	tmp = *arg;
	if (quo->slashes)
	{
		join_args2_utils(quo, tmp2, arg);
		if (quo->slashes != -1)
		{
			shut_escape(tmp_seq, quo);
			tmp2 = ft_genstr('\\', quo->slashes);
			*arg = ft_strjoin(*arg, tmp2);
			free(tmp2);
		}
	}
	else
	{
		tmp2 = ft_substr(tmp_seq->run, quo->start - tmp_seq->run, \
						quo->end - quo->start);
		*arg = ft_strjoin(*arg, tmp2);
		free(tmp2);
	}
	free(tmp);
	if (!*arg)
		error_quotes(&quo, &shell);
}

static void	join_args1(t_seq *tmp_seq, t_shell *shell, t_quo *quo, char **arg)
{
	if (quo->slashes)
	{
		if (quo->slashes == -1)
			*arg = ft_itoa(ret_status);
		else
		{
			shut_escape(tmp_seq, quo);
			*arg = ft_genstr('\\', quo->slashes);
		}
	}
	else
		*arg = ft_substr(\
		tmp_seq->run, quo->start - tmp_seq->run, quo->end - quo->start);
	if (!*arg)
		error_quotes(&quo, &shell);
	quo->split_len++;
	quo->after_space = 0;
}

void	join_args(t_seq *tmp_seq, t_shell *shell, t_quo *quo, \
				t_quo_split *tmp_split)
{
	if (quo->after_space && tmp_split->arg)
	{
		if (init_quo_split(&tmp_split->next))
			error_quotes(&quo, &shell);
		join_args1(tmp_seq, shell, quo, &tmp_split->next->arg);
	}
	else if (!tmp_split->arg)
		join_args1(tmp_seq, shell, quo, &tmp_split->arg);
	else
		join_args2(tmp_seq, shell, quo, &tmp_split->arg);
}

void	join_one_sym(t_shell *shell, t_quo *quo, char **str, char *sym)
{
	char	*tmp;

	tmp = *str;
	*str = ft_strjoin(*str, sym);
	free(tmp);
	if (!*str)
		error_quotes(&quo, &shell);
	quo->last_slash = 0;
	quo->end++;
}

void	join_routine(t_seq *tmp_seq, t_shell *shell, t_quo *quo, \
				t_quo_split *tmp_split)
{
	if ((quo->start != quo->end) || \
	(quo->start == quo->end && (*quo->end == '\'' || *quo->end == '"' || \
	*quo->end == '?')))
	{
		if (tmp_split)
			join_args(tmp_seq, shell, quo, tmp_split);
		else
		{
			if (!tmp_seq->tmp_redir->path)
			{
				tmp_seq->tmp_redir->path = ft_strdup("");
				if (!tmp_seq->tmp_redir->path)
					error_quotes(&quo, &shell);
			}
			join_args2(tmp_seq, shell, quo, &tmp_seq->tmp_redir->path);
		}
		quo->start = quo->end;
	}
}

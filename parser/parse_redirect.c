#include "../minibash.h"

static void try_redirect(t_seq *tmp_seq, t_shell *shell, char **end, char sym)
{
	char *start;

	++*end;
	start = *end;
	while (**end && **end == ' ')
		++*end;
	while (**end && **end != ' ')
		++*end;
	if (sym == '>')
	{
		tmp_seq->output = ft_strtrim(ft_substr(tmp_seq->run, \
							start - tmp_seq->run, *end - start), " ");
		if (!tmp_seq->output)
			free_error(strerror(errno), &shell);
		tmp_seq->info |= REDIR_OUT;
	}
	else if (sym == '<')
	{
		tmp_seq->input = ft_strtrim(ft_substr(tmp_seq->run, \
							start - tmp_seq->run, *end - start), " ");
		if (!tmp_seq->input)
			free_error(strerror(errno), &shell);
		tmp_seq->info |= REDIR_IN;
	}
}

static int join_args(char **space_join, char *start, char *end, t_seq *tmp_seq)
{
	char *tmp;

	tmp = *space_join;
	*space_join = ft_strjoin_space(*space_join, \
	ft_substr(tmp_seq->run, start - tmp_seq->run, end - start));
	free(tmp);
	if (!*space_join)
		return (1);
	return (0);
}

static void find_redirect(t_seq *tmp_seq, t_shell *shell, char **space_join, char *end)
{
	char *start;

	while (*end)
	{
		start = end;
		while (*end && *end != '>' && *end != '<')
			end++;
		if (*end)
		{
			if (join_args(space_join, start, end, tmp_seq))
				free_error(strerror(errno), &shell);
			try_redirect(tmp_seq, shell, &end, *end);
			end++;
		}
		else
		{
			if (join_args(space_join, start, end, tmp_seq))
				free_error(strerror(errno), &shell);
		}
	}
}

void	parse_redirect(t_seq *tmp_seq, t_shell *shell)
{
	char *end;
	char *space_join;
	char *tmp;

	if (!tmp_seq->run)
		tmp_seq->run = ft_strdup(shell->hist_curr->command);
	space_join = ft_strdup("");
	if (!space_join || !tmp_seq->run)
		free_error(strerror(errno), &shell);
	end = tmp_seq->run;
	find_redirect(tmp_seq, shell, &space_join, end);
	tmp = tmp_seq->run;
	tmp_seq->run = ft_strdup(space_join);
	free(tmp);
	if (!tmp_seq->run)
		free_error(strerror(errno), &shell);
}

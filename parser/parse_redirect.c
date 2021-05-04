#include "../minibash.h"

static void parse_input(t_redir_chain *tmp_redir, t_shell *shell)
{
	if (ft_strempty(tmp_redir->path))
		syntax_error(shell, '<');
	tmp_redir->type |= REDIR_IN;
}

static void parse_output(t_redir_chain *tmp_redir, t_shell *shell)
{
	if (ft_strempty(tmp_redir->path))
		syntax_error(shell, '>');
	if (!(tmp_redir->type & REDIR_APPEND))
		tmp_redir->type |= REDIR_OUT;
}

static int check_redirect(t_quo *quo, char sym, t_shell *shell, t_seq *tmp_seq)
{
	int i;

	i = 0;
	while (*quo->end == sym)
	{
		i++;
		if ((sym == '>' && i > 2) || (sym == '<' && i > 1))
		{
			syntax_error(shell, sym);
			return (0);
		}
		quo->end++;
	}
	return (i);
}

static void init_redirect(t_redir_chain **new, t_quo *quo, t_shell *shell)
{
	*new = (t_redir_chain *)malloc(sizeof(t_redir_chain));
	if (!*new)
		error_quotes(&quo, &shell);
	(*new)->path = NULL;
	(*new)->type = ZERO;
	(*new)->next = NULL;
}

// void redirect_join(t_seq *tmp_seq, t_shell *shell, t_quo *quo)
// {
// 	char *tmp;

// 	tmp = tmp_seq->tmp_redir->path;
// 	if (quo->slashes)
// 	{
// 		if (quo->slashes == 1 && quo->last_slash)
// 			quo->slashes = 0;
// 		tmp_seq->tmp_redir->path = ft_strjoin(tmp_seq->tmp_redir->path, \
// 		ft_genstr('\\', quo->slashes));
// 	}
// 	else
// 	{
// 		tmp_seq->tmp_redir->path = ft_strjoin(tmp_seq->tmp_redir->path, \
// 		ft_strtrim(ft_substr(\
// 		tmp_seq->run, quo->start - tmp_seq->run, quo->end - quo->start), "'\""));
// 	}
// 	free(tmp);
// 	if (!tmp_seq->tmp_redir->path)
// 		error_quotes(&quo, &shell);
// }

static void construct_file(t_seq *tmp_seq, t_shell *shell, t_quo *quo)
{
	tmp_seq->tmp_redir->path = ft_strdup("");
	if (!tmp_seq->tmp_redir->path)
		error_quotes(&quo, &shell);
	if (*quo->end == '|')
		quo->end++;
	while (*quo->end && *quo->end == ' ')
		quo->end++;
	while (*quo->end)
	{
		quo->start = quo->end;
		while (*quo->end && !ft_strchr(" $<>\"\\'", *quo->end))
			quo->end++;
		if (ft_strchr(" $<>\"'", *quo->end) && cancel_escape(tmp_seq, shell, quo, NULL))
			continue;
		join_routine(tmp_seq, shell, quo, NULL);
		if (ft_strchr(" <>", *quo->end))
			break;
		what_parse(tmp_seq, shell, quo, NULL);
		continue;
	}
}

void parse_redirect(t_seq *tmp_seq, t_shell *shell, t_quo *quo)
{
	static t_redir_chain *tmp_redir;
	char sym;
	int i;

	sym = *quo->end;
	i = check_redirect(quo, sym, shell, tmp_seq);
	if (shell->seq->info & SYNTAX_ERR)
		return;
	if (!tmp_seq->redirect)
	{
		init_redirect(&tmp_seq->redirect, quo, shell);
		tmp_redir = tmp_seq->redirect;
	}
	else
	{
		init_redirect(&tmp_redir->next, quo, shell);
		tmp_redir = tmp_redir->next;
	}
	tmp_seq->tmp_redir = tmp_redir;
	construct_file(tmp_seq, shell, quo);
	tmp_redir->path = ft_strdup(tmp_seq->tmp_redir->path);
	if (!tmp_redir->path)
		error_quotes(&quo, &shell);
	if (i == 2)
		tmp_redir->type |= REDIR_APPEND;
	if (sym == '>')
		parse_output(tmp_redir, shell);
	else if (sym == '<')
		parse_input(tmp_redir, shell);
}
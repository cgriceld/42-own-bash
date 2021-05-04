#include "../minibash.h"

static void parse_input(t_redir_chain *tmp_redir, t_seq *tmp_seq, t_shell *shell, t_quo *quo)
{
	tmp_redir->path = ft_strtrim(ft_substr(tmp_seq->run, \
							quo->start - tmp_seq->run, quo->end - quo->start), "< ");
	if (!tmp_redir->path)
		error_quotes(&quo, &shell);
	if (ft_strempty(tmp_redir->path))
		syntax_error(shell, '<');
	tmp_redir->type |= REDIR_IN;
}

static void parse_output(t_redir_chain *tmp_redir, t_seq *tmp_seq, t_shell *shell, t_quo *quo)
{
	tmp_redir->path = ft_strtrim(ft_substr(tmp_seq->run, \
							quo->start - tmp_seq->run, quo->end - quo->start), "> ");
	if (!tmp_redir->path)
		error_quotes(&quo, &shell);
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



// static void construct_file(t_shell *shell, t_quo *quo)
// {
// 	char *file;

// 	file = ft_strdup("");
// 	if (!file)
// 		error_quotes(&quo, &shell);
// 	if (*quo->end == '|')
// 		quo->end++;
// 	while (*quo->end && *quo->end == ' ')
// 		quo->end++;
// 	while (*quo->end && !ft_strchr(" $<>\"\\'", *quo->end))
// 	{
// 		if (*quo->end == '\'')

// 	}
// }

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
	while (*quo->end && *quo->end == ' ')
		quo->end++;
	while (*quo->end && *quo->end != ' ' && !ft_strchr("<>", *quo->end))
		quo->end++;
	if (i == 2)
		tmp_redir->type |= REDIR_APPEND;
	if (sym == '>')
		parse_output(tmp_redir, tmp_seq, shell, quo);
	else if (sym == '<')
		parse_input(tmp_redir, tmp_seq, shell, quo);
}
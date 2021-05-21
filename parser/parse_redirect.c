#include "../minibash.h"

static int	check_redirect(t_quo *quo, char sym, t_shell *shell, \
						t_seq *tmp_seq)
{
	int	i;

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

static void	init_redirect(t_redir_chain **new, t_quo *quo, t_shell *shell)
{
	*new = (t_redir_chain *)malloc(sizeof(t_redir_chain));
	if (!*new)
		error_quotes(&quo, &shell);
	(*new)->path = NULL;
	(*new)->type = ZERO;
	(*new)->next = NULL;
}

static void	construct_file(t_seq *tmp_seq, t_shell *shell, t_quo *quo)
{
	if (*quo->end == '|')
		quo->end++;
	while (*quo->end && *quo->end == ' ')
		quo->end++;
	if (*quo->end == '$')
		tmp_seq->tmp_redir->type |= AMBIGUOUS;
	while (*quo->end)
	{
		quo->start = quo->end;
		while (*quo->end && !ft_strchr(" $<>\"\\'", *quo->end))
			quo->end++;
		if (ft_strchr(" $<>\"'", *quo->end) && \
				cancel_escape(tmp_seq, shell, quo, NULL))
			continue ;
		join_routine(tmp_seq, shell, quo, NULL);
		if (ft_strchr(" <>", *quo->end))
			break ;
		what_parse(tmp_seq, shell, quo, NULL);
		continue ;
	}
}

static void	parse_redirect_utils(t_seq *tmp_seq, t_shell *shell, t_quo *quo, \
								t_redir_chain *tmp_redir)
{
	char	sym;
	int		i;

	sym = *quo->end;
	i = check_redirect(quo, sym, shell, tmp_seq);
	if (shell->seq->info & SYNTAX_ERR)
		return ;
	construct_file(tmp_seq, shell, quo);
	if (i == 2)
		tmp_redir->type |= REDIR_APPEND;
	if (tmp_redir->path)
		tmp_redir->type &= ~AMBIGUOUS;
	if (sym == '>')
		parse_output(tmp_redir, shell, quo);
	else if (sym == '<')
		parse_input(tmp_redir, shell, quo);
}

void	parse_redirect(t_seq *tmp_seq, t_shell *shell, t_quo *quo)
{
	static t_redir_chain	*tmp_redir;

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
	if (*quo->end == '<' && *(quo->end + 1) == '>' && \
			!ft_strchr("<>", *(quo->end + 2)))
	{
		quo->end++;
		tmp_seq->tmp_redir->type |= IGNORE;
	}
	parse_redirect_utils(tmp_seq, shell, quo, tmp_redir);
}

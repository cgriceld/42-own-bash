#include "../minibash.h"

static void parse_input(t_seq *tmp_seq, t_shell *shell, t_quo *quo, t_quo_split *tmp_split)
{
	tmp_seq->input = ft_strtrim(ft_substr(tmp_seq->run, \
							quo->start - tmp_seq->run, quo->end - quo->start), "< ");
	if (!tmp_seq->input)
		error_quotes(&quo, &shell);
	tmp_seq->info |= REDIR_IN;
	if ((tmp_seq->info & REDIR_IN) && ft_strempty(tmp_seq->input))
	{
		syntax_error(shell, '<');
		error_quotes(&quo, &shell);
	}
}

void parse_redirect(t_seq *tmp_seq, t_shell *shell, t_quo *quo, t_quo_split *tmp_split)
{
	char sym;

	sym = *quo->end;
	quo->end++;
	while (*quo->end && *quo->end == ' ')
		quo->end++;
	while (*quo->end && *quo->end != ' ')
		quo->end++;
	if (sym == '>')
	{
		tmp_seq->output = ft_strtrim(ft_substr(tmp_seq->run, \
							quo->start - tmp_seq->run, quo->end - quo->start), "> ");
		if (!tmp_seq->output)
			error_quotes(&quo, &shell);
		tmp_seq->info |= REDIR_OUT;
		if ((tmp_seq->info & REDIR_OUT) && ft_strempty(tmp_seq->output))
		{
			syntax_error(shell, '>');
			error_quotes(&quo, &shell);
		}
	}
	else if (sym == '<')
		parse_input(tmp_seq, shell, quo, tmp_split);
}
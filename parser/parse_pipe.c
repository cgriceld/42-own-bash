#include "../minibash.h"

static int syntax_error(char **trim, t_shell *shell)
{
	if (!**trim)
	{
		free(*trim);
		printf("-minibash: syntax error near unexpected token `|'\n");
		shell->seq->info |= SYNTAX_ERR;
		return (1);
	}
	return (0);
}

static void fill_lst_after_split(t_seq *tmp_seq, t_shell *shell, char **split)
{
	size_t	i;
	char	*trim;

	i = 0;
	while (split[i])
	{
		trim = ft_strtrim(split[i], " ");
		if (!trim)
			free_split(&split, shell);
		if (syntax_error(&trim, shell))
			break;
		tmp_seq->run = ft_strdup(trim);
		free(trim);
		if (!tmp_seq->run)
			free_split(&split, shell);
		if (split[i + 1] && init_seq(&tmp_seq->next))
			free_split(&split, shell);
		if (split[i + 1])
			tmp_seq->info |= PIPE;
		tmp_seq = tmp_seq->next;
		i++;
	}
	ft_twodarr_free(&split, ft_twodarr_len(split));
}

void parse_pipe(t_seq *tmp_seq, t_shell *shell)
{
	char **split;
	size_t len;

	split = ft_split(shell->hist_curr->command, '|');
	if (!split)
		free_error(strerror(errno), &shell);
	len = ft_twodarr_len(split);
	if (ft_numchstr(shell->hist_curr->command, '|') + 1 != len)
	{
		printf("-minibash: syntax error near unexpected token `|'\n");
		shell->seq->info |= SYNTAX_ERR;
		ft_twodarr_free(&split, ft_twodarr_len(split));
		return;
	}
	fill_lst_after_split(tmp_seq, shell, split);
	while (tmp_seq)
	{
		parse_one(tmp_seq, shell);
		tmp_seq = tmp_seq->next;
	}
}
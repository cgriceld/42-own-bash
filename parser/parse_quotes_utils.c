#include "../minibash.h"

int	init_quo_split(t_quo_split **new)
{
	*new = (t_quo_split *)malloc(sizeof(t_quo_split));
	if (!*new)
		return (1);
	(*new)->arg = NULL;
	(*new)->next = NULL;
	return (0);
}

void	free_quotes(t_quo **quo)
{
	t_quo_split	*tmp;

	while ((*quo)->split)
	{
		tmp = (*quo)->split;
		(*quo)->split = (*quo)->split->next;
		if (tmp->arg)
			free(tmp->arg);
		free(tmp);
	}
	free(*quo);
}

void	error_quotes(t_quo **quo, t_shell **shell)
{
	free_quotes(quo);
	free_error(strerror(errno), shell);
}

static void	fill_args(t_seq *tmp_seq, t_shell *shell, t_quo *quo, size_t i)
{
	tmp_seq->args[quo->split_len] = NULL;
	i = quo->split_len;
	while (i--)
		tmp_seq->args[i] = NULL;
}

void	fill_after_quotes(t_seq *tmp_seq, t_shell *shell, t_quo *quo)
{
	char		*tmp;
	t_quo_split	*tmp_s;
	size_t		i;

	tmp = tmp_seq->run;
	tmp_seq->run = ft_strdup(quo->split->arg);
	free(tmp);
	if (!tmp_seq->run && quo->split->arg)
		error_quotes(&quo, &shell);
	tmp_seq->args = (char **)malloc(sizeof(char *) * (quo->split_len + 1));
	if (!tmp_seq->args)
		error_quotes(&quo, &shell);
	fill_args(tmp_seq, shell, quo, i);
	if (!quo->split_len)
		return ;
	tmp_s = quo->split;
	i = 0;
	while (tmp_s)
	{
		tmp_seq->args[i] = ft_strdup(tmp_s->arg);
		if (!tmp_seq->args[i])
			error_quotes(&quo, &shell);
		tmp_s = tmp_s->next;
		i++;
	}
}

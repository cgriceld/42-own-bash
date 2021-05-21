#include "../minibash.h"

int	syntax_error(t_shell *shell, char sym)
{
	write(2, "-minibash: syntax error near unexpected token `", 47);
	write(2, &sym, 1);
	write(2, "'\n", 2);
	shell->seq->info |= SYNTAX_ERR;
	ret_status = 258;
	return (1);
}

void	trim_or_not(char *split, t_seq *tmp_seq)
{
	char	*sym;

	sym = ft_strrchr(split, '\\');
	if (!sym || (sym && *(sym - 1) == '\\' && even_escaped(split, ++sym)))
		tmp_seq->run = ft_strtrim(split, " ");
	else
		tmp_seq->run = ft_strdup(split);
}

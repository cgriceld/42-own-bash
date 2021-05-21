#include "../minibash.h"

int	quo_syntax_return(unsigned char f)
{
	if (f & DOUBLED)
		return (1);
	if (f & SINGLE)
		return (2);
	return (0);
}

int	even_escaped(char *start, char *str)
{
	int	res;

	res = 0;
	str--;
	while (str != start && *str == '\\')
	{
		res++;
		str--;
	}
	if (!(res % 2))
		return (1);
	else
		return (0);
}

void	manage_before(char **before, t_shell *shell, size_t len)
{
	if (!shell->seq->run)
		*before = ft_strdup("");
	else
		*before = ft_substr(shell->seq->run, 0, len);
}

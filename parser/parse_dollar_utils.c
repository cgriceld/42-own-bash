#include "../minibash.h"

void	error_dollar(char **value, t_quo *quo, t_shell *shell)
{
	free(*value);
	error_quotes(&quo, &shell);
}

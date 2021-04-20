#include "../minibash.h"

int builtins_to_exit(t_shell *shell)
{
	free_shell(&shell);
	exit(0);
}

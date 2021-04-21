#include "../minibash.h"

//добработать с аргкментом если плюс минус 256/

int builtins_exit(t_shell *shell)
{
	free_error(NULL, &shell);
	//принтнуть экзит
	exit(0);
}

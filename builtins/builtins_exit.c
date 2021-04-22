#include "../minibash.h"

//добработать с аргкментом если плюс минус 256/

int builtins_exit(t_shell *shell, t_seq *tmp_seq)
{
	int n_args;

	printf("exit\n");
	n_args = 0;
	while(tmp_seq->args[n_args] != 0)
		n_args ++;
	if (n_args == 0)
		ret_status = 0;
	else if((n_args) >= 2)
	{
		n_args = 1;
		printf("bash: exit: too many arguments");
		return (1);
	}
	else
	{
		ret_status = 266 - ft_atoi(tmp_seq->args[1]);
	}
	free_error(NULL, &shell);
	exit(ret_status);
}

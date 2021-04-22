#include "../minibash.h"

int too_many_args(void)
{
	printf("exit: too many arguments");
	ret_status = 1;
	return (ret_status);
}

int two_args(t_seq *tmp_seq)
{
	printf("exit: %s: numeric argument required", tmp_seq->args[1]);
	ret_status = 1;
	return (ret_status);
}

int builtins_exit(t_shell *shell, t_seq *tmp_seq)
{
	int n;
	int n_args;
	int num;

	printf("exit\n");
	ret_status = 0;
	n_args = 0;
	while(tmp_seq->args[n_args] != 0)
		n_args ++;
	n = ft_strlen(tmp_seq->args[1]);
	num = ft_atoi(tmp_seq->args[1]);
	else if (n_args == 2 && (num == 0 &&
			(n != 1 || (tmp_seq->args[1][0] != '0'))))
		return two_args(tmp_seq);
	else if ((n_args) > 2)
		return too_many_args(void);
	else if (num < 0)
		ret_status = num % 256 + 256;
	else if (num > 0)
		ret_status = 256 + num % 256;
	free_error(NULL, &shell);
	exit(ret_status);
}

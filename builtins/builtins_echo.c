#include "../minibash.h"

 int	builtins_echo(t_shell *shell, t_seq *tmp_seq)
{
	//	эти переменные будут взяты из парса
	char *param;

	int n;
	int i;
	ret_status = 0;

	n = 0;
	i = 1;
	param = ft_strtrim(tmp_seq->args[i], "\n");
	if (ft_strncmp(param, "-n", 3) == 0)
		n = 1;
	while(tmp_seq->args[i+n] != NULL)
	{
		printf("%s", ft_strtrim(tmp_seq->args[i+n], "\n"));
	}
	if (n == 1)
		printf("\n");
	return (0);
}

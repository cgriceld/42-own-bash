#include "../minibash.h"

 int	builtins_echo(t_shell *shell, t_seq *tmp_seq)
{
	int n;
	int i;
	char *tmp;

	ret_status = 0;
	n = 0;

	if (tmp_seq->args[1] != NULL)
	{
		if (ft_strncmp(ft_strtrim(tmp_seq->args[1], "\n"), "-n", 3) == 0)
			n = 1;
		i = 1;
		while (tmp_seq->args[i + n - 1] != NULL)
		{
			tmp = ft_strtrim(tmp_seq->args[i + n - 1], "\n");
			printf("%s ", tmp);
			free(tmp);
			i++;
		}
		if (tmp_seq->args[i + n] != NULL)
		{
			tmp = ft_strtrim(tmp_seq->args[i + n], "\n");
			printf("%s", tmp);
			free(tmp);
		}
		if (n == 0)
			printf("\n");
	}
	return (ret_status);
}

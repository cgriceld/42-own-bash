#include "../minibash.h"

 int	builtins_echo(t_shell *shell, t_seq *tmp_seq)
{
	//	эти переменные будут взяты из парса
	char *buf;
	char *param;

	param = NULL;
//	param = "n";
	buf = NULL;
//	buf = "builtins";
	buf = "/Users/sbrenton";

	(void)*shell;
	if (buf != NULL)
		printf("%s", buf);
	if (!param)
		printf("\n");
	return (0);
}

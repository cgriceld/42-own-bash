#include "../minibash.h"

void	ft_twodarr_free(char ***arr, size_t len)
{
	char	**tmp;

	tmp = *arr;
	while (len--)
	{
		if (tmp[len])
			free(tmp[len]);
	}
	free(tmp);
	*arr = NULL;
}

size_t	ft_twodarr_len(char **arr)
{
	size_t	len;

	len = 0;
	while (*arr++)
		len++;
	return (len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char const	*trimstart;

	if (!s1 || !set)
		return (NULL);
	if (!*set || !*s1)
		return (ft_strdup(s1));
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	trimstart = s1;
	while (*s1)
		s1++;
	while (s1 != trimstart && ft_strchr(set, *s1))
		s1--;
	return (ft_substr(trimstart, 0, s1 - trimstart + 1));
}

size_t	ft_numchstr(char *s, char ch)
{
	size_t	i;

	i = 0;
	while (*s)
	{
		if (*s++ == ch)
			i++;
	}
	return (i);
}

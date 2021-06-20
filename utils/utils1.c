#include "../minibash.h"

size_t	ft_strlen(const char *s)
{
	const char	*str;

	str = s;
	while (*str)
		str++;
	return (str - s);
}

char	*ft_strrchr(const char *s, int c)
{
	char		ch;
	const char	*res;

	ch = (char)c;
	res = NULL;
	while (*s)
	{
		if (*s == ch)
			res = s;
		s++;
	}
	if (*s == ch)
		return ((char *)s);
	else
		return ((char *)res);
}

char	*ft_strdup(const char *s1)
{
	char	*dup;
	char	*tmp;

	if (!s1)
		return (NULL);
	dup = (char *)malloc(ft_strlen(s1) + 1);
	if (!dup)
		return (NULL);
	tmp = dup;
	while (*s1)
		*tmp++ = *s1++;
	*tmp = '\0';
	return (dup);
}

char	*ft_genstr(char sym, int num)
{
	char	*gen;
	char	*str;

	gen = (char *)malloc(sizeof(num + 1));
	if (!gen)
		return (NULL);
	str = gen;
	while (num--)
		*str++ = sym;
	*str = '\0';
	return (gen);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	char	*tmp;

	if (!s1 || !s2)
		return (NULL);
	join = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!join)
		return (NULL);
	tmp = join;
	while (*s1)
		*tmp++ = *s1++;
	while (*s2)
		*tmp++ = *s2++;
	*tmp = '\0';
	return (join);
}

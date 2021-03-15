#include "base.h"

size_t	ft_strlen(const char *s)
{
	const char *str;

	str = s;
	while (*str)
		str++;
	return (str - s);
}

char	*ft_strdup(const char *s1)
{
	char *dup;
	char *tmp;

	dup = (char *)malloc(ft_strlen(s1) + 1);
	if (!dup)
		return (NULL);
	tmp = dup;
	while (*s1)
		*tmp++ = *s1++;
	*tmp = '\0';
	return (dup);
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

int		ft_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}
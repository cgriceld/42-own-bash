#include "../minibash.h"

char	*ft_strjoin_sym(char const *s1, char const *s2, char sym)
{
	char	*join;
	char	*tmp;

	if (!s1 || !s2)
		return (NULL);
	join = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
	if (!join)
		return (NULL);
	tmp = join;
	while (*s1)
		*tmp++ = *s1++;
	*tmp++ = sym;
	while (*s2)
		*tmp++ = *s2++;
	*tmp = '\0';
	return (join);
}

char	*ft_strjoin_space(char const *s1, char const *s2)
{
	char	*join;
	char	*tmp;

	if (!s1 || !s2)
		return (NULL);
	join = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
	if (!join)
		return (NULL);
	tmp = join;
	while (*s1)
		*tmp++ = *s1++;
	*tmp++ = ' ';
	while (*s2)
		*tmp++ = *s2++;
	*tmp = '\0';
	return (join);
}

int	ft_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*tmp;

	if (len)
	{
		tmp = (unsigned char *)b;
		while (len--)
			*tmp++ = (unsigned char)c;
	}
	return (b);
}

void	ft_bzero(void *s, size_t n)
{
	if (n)
		ft_memset(s, 0, n);
}

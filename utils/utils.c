#include "../minibash.h"

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

char *ft_genstr(char sym, int num)
{
	char *gen;
	char *str;

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

int		ft_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char *tmp;

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

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	const unsigned char *str1;
	unsigned char		*str2;

	if ((s1 && (s1 == s2)) || !n)
		return (0);
	str1 = (const unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (n-- && (*str1 || *str2))
	{
		if (*str1++ != *str2++)
			return (*(--str1) - *(--str2));
	}
	return (0);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		sublen;
	char const	*substart;
	char		*substr;
	char		*tmp;

	if (!s)
		return (NULL);
	while (start-- && *s)
		s++;
	substart = s;
	while (len-- && *s)
		s++;
	sublen = s - substart;
	substr = (char *)malloc(sublen + 1);
	if (!substr)
		return (NULL);
	tmp = substr;
	while (sublen--)
		*tmp++ = *substart++;
	*tmp = '\0';
	return (substr);
}

char	*ft_strchr(const char *s, int c)
{
	char ch;

	ch = (char)c;
	while (*s && *s != ch)
		s++;
	return (*s == ch ? (char *)s : NULL);
}

int	ft_isdigit(int c)
{
	return (c >= 48 && c <= 57);
}

static int	ft_issign(const char c)
{
	return (c == 43 || c == 45);
}

static int	ft_isspace(const char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

int			ft_atoi(const char *str)
{
	long long int	prevn;
	long long int	n;
	int				sign;

	n = 0;
	sign = 1;
	while (*str && ft_isspace(*str))
		str++;
	if (ft_issign(*str) && *str++ == '-')
		sign = -1;
	while (*str && ft_isdigit(*str))
	{
		prevn = n;
		n = 10 * n + sign * (*str++ - 48);
		if (n > prevn && sign == -1)
			return (0);
		if (n < prevn && sign == 1)
			return (-1);
	}
	return (n);
}

static int	ft_nlen(int n)
{
	int i;

	i = n <= 0 ? 1 : 0;
	while (n)
	{
		i++;
		n /= 10;
	}
	return (i);
}

char		*ft_itoa(int n)
{
	int		len;
	int		sign;
	char	*str;

	len = ft_nlen(n);
	sign = n < 0 ? -1 : 1;
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	str += len;
	*str-- = '\0';
	if (!n)
		*str = '0';
	while (n)
	{
		*str = sign * (n % 10) + 48;
		if (n > 9 || n < -9)
			str--;
		n /= 10;
	}
	if (sign < 0)
		*--str = '-';
	return (str);
}

void	ft_twodarr_free(char ***arr, size_t len)
{
	char **tmp;

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
	size_t len;

	len = 0;
	while (*arr++)
		len++;
	return (len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char const *trimstart;

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

size_t		ft_numchstr(char *s, char ch)
{
	size_t i;

	i = 0;
	while (*s)
	{
		if (*s++ == ch)
			i++;
	}
	return (i);
}

char	*ft_strchrset(char *s, char *set)
{
	char *tmp;

	tmp = s;
	while (*s && !ft_strchr(set, *s))
		s++;
	return (!*s ? NULL : s);
}

int		ft_strempty(char *s)
{
	while (*s == ' ')
		s++;
	if (*s == '\0')
		return (1);
	return (0);
}

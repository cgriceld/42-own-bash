#include "../minibash.h"

static int	ft_getwords(char *s, const char c)
{
	int		words;
	char	*start;

	words = 0;
	start = s;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s++ != c)
			words++;
		while (*s)
		{
			if (*s != c || (*s == c && *(s - 1) == '\\') || \
		(*s == '|' && *(s - 1) == '>' && even_escaped(start, s - 1)))
				s++;
			else
				break ;
		}
	}
	return (words);
}

static void	ft_copyword(char *dst, const char *src, size_t letters)
{
	while (--letters)
		*dst++ = *src++;
	*dst = '\0';
}

static int	ft_putwords(char *s, char c, int words, char **split)
{
	char		*start;
	int			w;
	size_t		letters;

	w = 0;
	while (words--)
	{
		while (*s && *s == c)
			s++;
		start = s;
		while (*s)
		{
			if (*s != c || (*s == c && *(s - 1) == '\\') || \
	(*s == '|' && *(s - 1) == '>' && even_escaped(start, s - 1)))
				s++;
			else
				break ;
		}
		letters = s - start;
		split[w] = (char *)malloc(letters + 1);
		if (!split[w])
			return (w);
		ft_copyword(split[w++], start, letters + 1);
	}
	return (0);
}

char	**ft_split(char const *s, char c)
{
	int		words;
	int		error;
	char	**split;

	if (!s)
		return (NULL);
	words = ft_getwords((char *)s, c);
	split = (char **)malloc(sizeof(char *) * (words + 1));
	if (!split)
		return (NULL);
	split[words] = NULL;
	error = ft_putwords((char *)s, c, words, split);
	if (!error)
		return (split);
	while (error--)
		free(split[error]);
	free(split);
	return (NULL);
}

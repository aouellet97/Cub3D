#include "cub3d.h"


static int	count_words(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if ((s[i] != c) && ((s[i + 1] == c) || (s[i + 1] == 0)))
			count++;
		i++;
	}
	return (count);
}

static int	allocation(char **tab, char const *s, char c)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	start = 0;
	while (s[i])
	{
		if ((s[i] != c) && (i == 0))
			start = i;
		else if ((s[i] != c) && (s[i - 1] == c))
			start = i;
		if ((s[i] != c) && ((s[i + 1] == c) || (s[i + 1] == 0)))
		{
			tab[j] = gc_substr(s, start, i - start + 1);
			j++;
		}
		i++;
	}
	return (0);
}

char	**gc_split(char const *s, char c)
{
	char	**tab;
	int		words;
	int		result;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	tab = (char **)gc_malloc(sizeof(char *) * (words + 1));
	tab[words] = NULL;
	result = allocation(tab, s, c);
	if (result == 1)
		return (NULL);
	return (tab);
}
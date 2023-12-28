#include "cub3d.h"

char	*gc_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	size_t	size;

	if (!s1 && s2)
		return (gc_strdup(s2));
	else if (!s1 || !s2)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2);
	new_str = (char *)gc_malloc(sizeof(char) * (size + 1));
	ft_strlcpy(new_str, s1, size + 1);
	ft_strlcat(new_str, s2, size + 1);
	return (new_str);
}

char	*gc_strdup(const char *s1)
{
	char	*copy;
	size_t	len;
	size_t	i;

	if (!s1)
		return (0);
	len = ft_strlen(s1);
	i = 0;
	copy = (char *)gc_malloc(sizeof(char) * len + 1);
	while (i < len + 1)
	{
		copy[i] = s1[i];
		i++;
	}
	return (copy);
}

static void	create_str(char const *s, char *new_str, unsigned int start,
		size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[start + j])
	{
		if (i < len)
		{
			new_str[i] = s[start + i];
			i++;
		}
		j++;
	}
	new_str[i] = '\0';
}

char	*gc_substr(char const *s, unsigned int start, size_t len)
{
	char	*new_str;
	size_t	m_size;

	if (!s)
		return (0);
	if (start >= ft_strlen(s))
	{
		len = 0;
		m_size = 0;
	}
	m_size = ft_strlen(s) - start;
	if (len < m_size)
		m_size = len;
	new_str = (char *)gc_malloc(sizeof(char) * (m_size + 1));
	if (m_size == 0)
	{
		*new_str = 0;
		return (new_str);
	}
	create_str(s, new_str, start, len);
	return (new_str);
}

void	*gc_calloc(size_t nmemb, size_t size)
{
	char	*ptr;
	size_t	i;

	ptr = (char *)gc_malloc(nmemb * size);
	i = 0;
	while (i < nmemb * size)
		ptr[i++] = 0;
	return ((void *)ptr);
}

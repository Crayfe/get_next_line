/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayuso-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:31:19 by cayuso-f          #+#    #+#             */
/*   Updated: 2024/10/04 14:21:01 by cayuso-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

/*	AUXILIAR FUNCTIONS	*/
void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*aux_s;

	i = 0;
	aux_s = (unsigned char *)s;
	while (i < n)
		aux_s[i++] = c;
	return (s);
}
size_t	ft_strlen(const char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i] != c)
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)s + i);
	return (0);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	aux_len;

	if (!s)
		return (0);
	if ((size_t) start > ft_strlen(s))
	{
		sub = (char *)malloc(1);
		*sub = 0;
		return (sub);
	}
	if (len > ft_strlen(s) - (size_t) start)
		aux_len = ft_strlen(s) - (size_t) start;
	else
		aux_len = len;
	sub = (char *)malloc(aux_len + 1);
	if (!sub)
		return (0);
	ft_strlcpy(sub, s + start, aux_len + 1);
	return (sub);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	if (size == 0)
		return (ft_strlen(src));
	i = 0;
	while (src[i] && i < (size - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	k;

	i = ft_strlen(dst);
	k = ft_strlen(src);
	if ((!dst || !src) && size == 0)
		return (0);
	if (size < i)
		return (size + k);
	ft_strlcpy(dst + i, src, size - i);
	return (i + k);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	int		len1;
	int		len2;

	if (!s1 || !s2)
		return (0);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	join = (char *)malloc((len1 + len2 + 1) * sizeof(char));
	if (!join)
		return (0);
	ft_strlcpy(join, s1, len1 + 1);
	ft_strlcat(join, s2, len1 + len2 + 1);
	return (join);
}



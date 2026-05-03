/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilcelik <ilcelik@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 17:20:58 by ilcelik           #+#    #+#             */
/*   Updated: 2026/05/02 17:20:58 by ilcelik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if ((char)c == '\0')
		return ((char *)(s + i));
	return (NULL);
}

static void	ft_fill(char *dst, char *src, size_t start)
{
	size_t	i;

	if (!src)
		return ;
	i = 0;
	while (src[i])
	{
		dst[start + i] = src[i];
		i++;
	}
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*result;
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = malloc(len1 + len2 + 1);
	if (!result)
	{
		free(s1);
		return (NULL);
	}
	ft_fill(result, s1, 0);
	ft_fill(result, s2, len1);
	result[len1 + len2] = '\0';
	free(s1);
	return (result);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	i;
	size_t	slen;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if ((size_t)start >= slen)
		len = 0;
	else if (len > slen - start)
		len = slen - start;
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (i < len)
	{
		result[i] = s[start + i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

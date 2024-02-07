/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  ctokoyod < ctokoyod@student.42tokyo.jp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 14:36:26 by  ctokoyod         #+#    #+#             */
/*   Updated: 2024/02/07 20:16:56 by  ctokoyod        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*gnl_strdup(const char *s1)
{
	char	*p;
	size_t	s_len;
	int		i;

	s_len = gnl_strlen(s1, "");
	p = (char *)malloc(sizeof(char) * (s_len + 1));
	if (p == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

size_t	gnl_strlen(char *s)
{
	size_t	len;

	// 文字列sの文字列cまでのバイト数を返す。なければsの文字列を返す。
	len = 0;
	while (s[len] != '\0')
	{
		len++;
	}
	return (len);
}

// memcopy
void	*gnl_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*uc_dst;
	const unsigned char	*uc_src;
	size_t				i;

	if (dst == NULL && src == NULL)
		return (NULL);
	uc_dst = (unsigned char *)dst;
	uc_src = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		uc_dst[i] = uc_src[i];
		i++;
	}
	return ((void *)dst);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	size_t s1_len;
	size_t s2_len;
	char *result;
	char *dest;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	result = (char *)malloc(sizeof(char) * s1_len + s2_len + 1);
	if (result == NULL)
		return (NULL);
	dest = result;
	gnl_memcpy(dest, s1, s1_len);
	gnl_memcpy(dest + s1_len, s2, s2_len);
	result[s1_len + s2_len] = '\0';
	return (result);
}
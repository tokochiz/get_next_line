/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  ctokoyod < ctokoyod@student.42tokyo.jp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 14:36:26 by  ctokoyod         #+#    #+#             */
/*   Updated: 2024/02/08 19:12:24 by  ctokoyod        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*trim_s;
	size_t	s_len;
	size_t	i;

	if (s == NULL)
		return (NULL);
	i = 0;
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (len >= s_len - start)
		len = s_len - start;
	trim_s = (char *)malloc(sizeof(char) * len + 1);
	if (trim_s == NULL)
		return (NULL);
	while (i < len)
	{
		trim_s[i] = s[start + i];
		i++;
	}
	trim_s[len] = '\0';
	return (trim_s);
}

char	*ft_strdup(const char *s1)
{
	char	*p;
	size_t	s_len;
	int		i;

	s_len = ft_strlen(s1);
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

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
	{
		len++;
	}
	return (len);
}
char	*ft_strchr(const char *s, int c)
{
	char	target_pos;

	target_pos = (char)c;
	while (*s != '\0')
	{
		if (*s == target_pos)
			return ((char *)s);
		s++;
	}
	if (target_pos == '\0')
		return ((char *)s);
	return (NULL);
}

// memcpy を使わない方式に書き換える
void	*ft_memcpy(void *dst, const void *src, size_t n)
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

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*result;
	char	*dest;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	result = (char *)malloc(sizeof(char) * s1_len + s2_len + 1);
	if (result == NULL)
		return (NULL);
	dest = result;
	ft_memcpy(dest, s1, s1_len);
	ft_memcpy(dest + s1_len, s2, s2_len);
	result[s1_len + s2_len] = '\0';
	return (result);
}

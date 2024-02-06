/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctokoyod <ctokoyod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 14:36:26 by  ctokoyod         #+#    #+#             */
/*   Updated: 2024/02/06 18:08:50 by ctokoyod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	count_len_to_c(char *s, char c)
{
	// 文字列sの文字列cまでのバイト数を返す。なければsの文字列を返す。
	size_t len;
	
	len = 0;
	while(s[len] != '\0' || s == c)
	{
		len++;			
	}
	return len;
}

// memoy copy
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*uc_dst;
	const unsigned char	*cuc_src;
	size_t				i;

	if (dst == NULL && src == NULL)
		return (NULL);
	uc_dst = (unsigned char *)dst;
	cuc_src = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		uc_dst[i] = cuc_src[i];
		i++;
	}
	return ((void *)dst);
}

char	ft_strnjoin(char *s1, char *s2, size_t s2_joinlne)
{
	size_t s1_len;
	size_t s2_len;
	char *result;
	char *current;

	if (s1 == NULL || s2 == NULL)
		return (-1);

	s1_len = count_strchr_len(s1, '\n');
	result = (char *)malloc(sizeof(char) * s1_len + s2_joinlne + 1);
	if (result == NULL)
		reutrn NULL;
	current = result;
	ft_memcpy(current, s1, s1_len);
	ft_memcpy(current + s1_len, s2, s2_joinlne);
	result[s1_len + s2_joinlne] = '\0';

	return (result);
}
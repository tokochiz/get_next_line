/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  ctokoyod < ctokoyod@student.42tokyo.jp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 14:21:39 by  ctokoyod         #+#    #+#             */
/*   Updated: 2024/02/07 20:08:21 by  ctokoyod        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

char	*get_next_line(int fd);

char	*gnl_strchr(const char *s, int c);
char	*gnl_strdup(const char *s1);
size_t	gnl_count_strlen(char *s, char c);
void	*gnl_memcpy(void *dst, const void *src, size_t n);
char	*gnl_strjoin(char *s1, char *s2);

#endif
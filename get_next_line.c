/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  ctokoyod < ctokoyod@student.42tokyo.jp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 16:45:06 by  ctokoyod         #+#    #+#             */
/*   Updated: 2024/02/09 18:26:42 by  ctokoyod        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// char	*releace_memory(char *line)
// {
// }

static char	*get_line_from_save(char **save)
{
	char	*line;
	char	*next_line;
	int		i;

	if (ft_strchr(*save, '\n') == NULL)
	{
		line = ft_strdup(*save);
		free(*save);
		*save = NULL;
		return (line);
	}
	else
	{
		i = 0;
		while ((*save)[i] != '\n')
			i++;
		line = ft_substr(*save, 0, i + 1);
		next_line = ft_strdup(*save + i + 1);
		free(*save);
		*save = next_line;
		return (line);
	}
}

static char	*read_file(int fd, char *buffer, char *joined)
{
	ssize_t	read_bytes;

	read_bytes = 1;
	while (read_bytes > 0 && !strchr(joined, '\n'))
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
			return (NULL);
		if (read_bytes == 0)
			break ;
		buffer[read_bytes] = '\0';
		joined = ft_strjoin(joined, buffer);
	}
	if (read_bytes == 0 && ft_strlen(joined) == 0)
		return (NULL);
	free(buffer);
	return (joined);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*buffer;
	char		*joined;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);
	joined = strdup("");
	if (joined == NULL)
	{
		free(buffer);
		return (NULL);
	}
	if (save == NULL)
		save = read_file(fd, buffer, joined);
	if (save == NULL)
		return (NULL);
	return (get_line_from_save(&save));
}

// int	main(void)
// {
// 	int fd;
// 	char *line;

// 	// テキストファイルを開く
// 	fd = open("test1.txt", O_RDONLY);
// 	if (fd < 0)
// 	{
// 		perror("Failed to open file");
// 		return (1);
// 	}

// 	// ファイルの内容を1行ずつ読み込む
// 	while ((line = get_next_line(fd)))
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}

// 	// ファイルを閉じる
// 	close(fd);

// 	return (0);
// }
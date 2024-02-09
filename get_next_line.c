/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  ctokoyod < ctokoyod@student.42tokyo.jp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 14:33:36 by  ctokoyod         #+#    #+#             */
/*   Updated: 2024/02/09 16:17:11 by  ctokoyod        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// メモリ領域を解放するための関数
static void	release_memory_area(char **line)
{
	if (*line == NULL)
		return ;
	free(*line);
	*line = NULL;
}

static char	*find_one_line(char *line)
{
	int		i;
	char	*remaining_text;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == '\0')
		return (NULL);
	// remaining_text = ft_strdup(line + i + 1);
	remaining_text = ft_substr(line, i + 1, (ft_strlen(line) - i));
	if (*remaining_text == '\0') // もし抽出した部分が空だったら
	{
		return NULL;
	}
	line[i + 1] = '\0'; // 元の文字列に終端文字を設定する
	return (remaining_text);
}

static char	*read_fd(int fd, char *buffer, char **line)
{
	char	*tmp_line;
	ssize_t	read_bytes;

	read_bytes = 1;
	while ((read_bytes) != 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
			return (NULL);
		if (read_bytes == 0)
			break ;
		buffer[read_bytes] = '\0'; // バッファの終端を設定
		if (*line == NULL)         // 既存のlineがからの場合とNULLの場合を考慮
			*line = ft_strdup(buffer);
		else
		{
			tmp_line = ft_strjoin(*line, buffer);
			if (tmp_line == NULL)
				return (NULL);
			free(*line);
			*line = tmp_line;
			if (ft_strchr(buffer, '\n'))
				break ;
		}
	}
	free(buffer);
	return (*line);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*save;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL); // ERROR処理
	buffer = malloc(BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (NULL); // ERROR処理
	if (save == NULL)
		save = ft_strdup("");
	line = read_fd(fd, buffer, &save);
	// free(buffer);
	if (line < 0)
	{
		release_memory_area(&line);
	}
	if (line == 0 && ft_strlen(line) == 0)
	{
		release_memory_area(&line);
		return (NULL);
	}
	return (find_one_line(line));
}

int	main(void)
{
	int fd;
	char *line;

	// テキストファイルを開く
	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
	{
		perror("Failed to open file");
		return (1);
	}

	// ファイルの内容を1行ずつ読み込む
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}

	// ファイルを閉じる
	close(fd);

	return (0);
}



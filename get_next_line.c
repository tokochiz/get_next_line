/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  ctokoyod < ctokoyod@student.42tokyo.jp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 14:33:36 by  ctokoyod         #+#    #+#             */
/*   Updated: 2024/02/08 20:42:48 by  ctokoyod        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// メモリ領域を解放するための関数
static void	release_memory_area(char *line)
{
	if (line == NULL)
		return ;
	free(line);
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
	remaining_text = ft_substr(line, i + 1, ft_strlen(line));
	if (*remaining_text == '\0')
	{
		release_memory_area(line);
		return (NULL);
	}
	line[i] = '\0';
	return (remaining_text);
}
// get-next-lineから返された行で、改行文字の直後の文字列を切り出す　
// 切り出した文字列はsave_str 残りの部分は元のlineから消す
static char	*read_fd(int fd, char *read_buffer, char *save_str)
{
	char	*tmp_save;
	ssize_t	read_bytes;

	read_bytes = 1;
	while (read_bytes != 0)
	{
		read_bytes = read(fd, read_buffer, BUFFER_SIZE);
		printf("***********************************readfd*[%zd]\n", read_bytes);
		if (read_bytes == -1)
			return (NULL);
		printf("********1\n");
		if (read_bytes == 0)
			break ;
		printf("********2\n");
		read_buffer[read_bytes] = '\0'; // バッファの終端を設定
		if (save_str == NULL)
			save_str = ft_strdup("");
		tmp_save = save_str;
		save_str = ft_strjoin(tmp_save, read_buffer);

		free(tmp_save);
		if (ft_strchr(read_buffer, '\n'))
			break ;
	}
	printf("********3\n");
	// printf("*********%d\n", fd);
	return (save_str);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buffer;
	static char	*save_str[OPEN_MAX];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (NULL);
	line = read_fd(fd, buffer, save_str[fd]);
	printf("********4\n");
	free(buffer);
	if (line == NULL)
	{
		save_str[fd] = find_one_line(save_str[fd]);
	}
	return (line);
}

int	main(void)
{
	int fd;
	char *line;

	// テキストファイルを開く
	fd = open("test_line3.txt", O_RDONLY);
	if (fd < 0)
	{
		perror("Failed to open file");
		return (1);
	}

	// ファイルの内容を1行ずつ読み込む
	while ((line = get_next_line(fd)))
	{
		printf("%s\n", line);
		free(line);
	}

	// ファイルを閉じる
	close(fd);

	return (0);
}
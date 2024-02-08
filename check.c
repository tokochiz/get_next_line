/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  ctokoyod < ctokoyod@student.42tokyo.jp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 14:33:36 by  ctokoyod         #+#    #+#             */
/*   Updated: 2024/02/08 22:06:26 by  ctokoyod        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// メモリ領域を解放するための関数
static void	release_memory_area(char **line)
{
	if (line == NULL)
		return ;
	free(line);
}

static char	*find_one_line(char **line)
{
	size_t	i;
	char	*remaining_text;
	

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == '\0')
		return (NULL);
	remaining_text = ft_substr(line, i + 1, (ft_strlen(line) - (i + 1 + 1))); //改行文字分0+インデックス
	*line = remaining_text;
	line[i+1+ if (*remaining_text == '\0')
	{
		release_memory_area(line);
		return (NULL);
	}
	line[i] = '\0';
	return (remaining_text);
}
ssize_t	read_fd(int fd, char *read_buffer, char *line)
{
	char *tmp_save; //一時保存buffer
	read_bytes = 1;
	while (read_bytes != 0) //
	{
		read_bytes = read(fd, read_buffer, BUFFER_SIZE);
		if (read_bytes == -1)
			return (NULL);
		read_buffer[read_bytes] = '\0'; // バッファの終端を設定
		tmp_save = line;
		line = ft_strjoin(tmp_save, read_buffer);
		if (line == NULL)
			return (-1);
		free(tmp_save);
		if (ft_strchr(read_buffer, '\n'))
			break ;
	}
	return (read_bytes);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*buffer;

	ssize_t read_bytes; //戻り値
	// static char	*save_str[OPEN_MAX];
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);                //エラー処理
	buffer = malloc(BUFFER_SIZE + 1); // buffer確保
	if (buffer == NULL)
		return (NULL); //エラー処理malloc失敗
	if (line == NULL)
		line = ft_strdup("");
	if (line == NULL)
		return (NULL); //エラー処理malloc失敗
	read_bytes = read_fd(fd, buffer, line);
	free(buffer);
	if (read_bytes < 0)
	{
		ft_strdel(&line);
		return (NULL);
	}
	if (read_bytes == 0 && *line == "")
	{
		ft_strdel(&line);
		return (NULL);
	}
	return (find_one_line(&line));
}
// int	main(void)
// {
// 	int fd;
// 	char *line;

// 	// テキストファイルを開く
// 	fd = open("test_line3.txt", O_RDONLY);
// 	if (fd < 0)
// 	{
// 		perror("Failed to open file");
// 		return (1);
// 	}

// 	// ファイルの内容を1行ずつ読み込む
// 	while ((line = get_next_line(fd)))
// 	{
// 		printf("%s\n", line);
// 		free(line);
// 	}

// 	// ファイルを閉じる
// 	close(fd);

// 	return (0);
// }
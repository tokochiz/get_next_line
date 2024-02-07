/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  ctokoyod < ctokoyod@student.42tokyo.jp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 14:33:36 by  ctokoyod         #+#    #+#             */
/*   Updated: 2024/02/07 20:14:55 by  ctokoyod        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// メモリ領域を解放するための関数
static void	release_memory_area(char **line)
{
	if (line == NULL)
		return ;
	free(*line);
	*line = NULL;
}

static int find_one_line(char **line)
{
	char	*newline_ptr;
	char *	newline_len;
	char	*remaining_text;

	newline_ptr = gnl_strchr(*line, '\n'); // 改行までの文字数を取ってくる
	// 改行が見つかったら
	if (newline_ptr != NULL)
	{
		newline_len = newline_ptr - *line; // 改行までの文字数
		*line = gnl_strdup(newline_len);
		if (*line == NULL)
			return (-1); // メモリ割り当て失敗
		//改行より後ろのテキストを残りのテキストとしてせっと
		remaining_text = gnl_strdup(newline_ptr + 1);
		if (*remaining_text == NULL)
		{
			free(*line);
			return (-1);
		}
		return (remaining_text); // 残りのテキストを返す
	}
	else
	{
		// 改行が見つからなかった場合 buf 全体の内容をline にコピー
		*line = gnl_strdup();
		if (*line == NULL)
			return (-1);
		// remainting_texgtはからに空に設定する
		return (0); // 残りのテキストは空
	}
}

/*
	指定されたファイルディスクリプたからデータを読みとり、それを文字列に追加する関数
	BUFFER_SIZEのバッファを作成し、新しい文字列を作成
	読み取ったデータを既存の文字列に追加
	読み取りが終了したらバッファを解放hして読み取り￥バイト数を返す
*/
static int	read_fd(int fd, char **line)
{
	ssize_t	read_bytes;
	char	*read_buffer;

	read_buffer = (char *)malloc((size_t)BUFFER_SIZE + 1);
	if (read_buffer == NULL)
		return (-1);
	read_bytes = read(fd, read_buffer, BUFFER_SIZE);
	while (read_bytes > 0)
	{
		// バッファの終端を設定
		read_buffer[read_bytes] = '\0';
		*line = gnl_strjoin(*line, read_buffer);
		if (*line == NULL)
		{
			free(read_buffer);
			return (-1);
		}
	}
	free(read_buffer);
	if (read_bytes < 0) // 読み取りエラー
		return (-1);
	else if (read_bytes == 0 && *line && **line == '\0')
	{
		free(*line);
		*line = NULL;
		return (0);
	}
	else
		return (1); // read ERROR
}

char	*get_next_line(int fd)
{
	static char	*line;
	ssize_t		read_bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_bytes = read_fd(fd, &line);
	if (read_bytes < 0) //  読み取り失敗
	{
		release_memory_area(&line);
		return (NULL);
	}
	if (read_bytes == 0 && gnl_count_strlen(*line) == 0) // データが空の時
	{
		release_memory_area(&line);
		return (NULL);
	}
	return (find_one_line(&line));
}

int	main(void)
{
	int fd = open("./test_line3.txt", O_RDONLY);
	char *line;
	int read_result;

	if(fd == -1)
	{
		fprintf(stdout, "faile open ERROR\n");
		return (1);
	}

	// FILEから1行ずつ読み取り、lineに格納し、読み取り結果を表示
	while (read_result == get_next_line(fd) > 0)
	{
		printf("%s\n", line);
	}
	if(read_result == 0)
		printf("Reached end of file\n");
	else
		printf("Error occurred while reading\n");
	close(fd);
	return 0;
}
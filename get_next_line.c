/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctokoyod <ctokoyod@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 14:33:36 by  ctokoyod         #+#    #+#             */
/*   Updated: 2024/02/06 18:35:11 by ctokoyod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*fined_newline(int fd, char **line, char **st_arr, char *buf)
{
	int new_line_len;
	
	new_line_len = count_len_to_c(buf, '\n');// 改行までの文字数を取ってくる
	if(new_line_len < BUFFER_SIZE)
	{
		// 改行がみつかった場合
	*line = ft_strnjoin(*line, buf, new_line_len);
	if(*line == NULL){
		return -1; // メモリ割り当て失敗
	}

//　改行以降をst_arrにコピー
	st_arr = ft_strdup(buf + new_line_len + 1);
	if(st_arr == NULL){
		free(*line);
		return -1;
	}

	return 1;

	}else if(new_line_len == BUFFER_SIZE ){	
	// TODO ;改行が見つからなかった場合
	*line = ft_strnjoin(*line, buf, strlen(buf));
	if(*line == NULL)
		return -1;

	free(st_arr); //st_arr を空にする
	st_arr = NULL;

	return 0;
}
	
}
/*
BUFFER_SIZE 分だけ read を使ってファイルディスクリプタから読み込み
読み込んだデータを st_arr に追加
find_newline を呼び出して改行があるかどうかを確認
*/

static int	read_fd(int fd, char **line, char **st_arr)
{
	char	*buf;
	int		read_bytes;
	int		result;

	buf = (char *)malloc(BUFFER_SIZE + 1);
	if (buf == NULL)
	return -1;
	if (st_arr != NULL) // st_arrが存在すれば、そこから先を先をlineにコピー
	{
		result = find_newline(fd, line, st_arr);
		if (result != 0)
			return result;
	}
	// BUFFER_SIZE だけ読み込んで処理を続ける
	while ((read_bytes = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[read_bytes] = '\0'; // バッファの終端を設定
		result = find_newline(fd, line, buf);
		if (result != 0)
			return (result);
	}
	// ファイルの終端に達した場合
	if (read_bytes == 0)
	{
		free(*st_arr);
		*st_arr = NULL;
		return -1;
	}
	return (-1); // read ERROR
}

char	*get_next_line(int fd)
{
	static char **st_arr;
	free(*st_arr);
	st_arr = NULL;

	// TODO: やること　関数を呼び出すために、指定したファイルの行を取ってくる
	// ファイル読み取り
	read_fd(BUFFER_SIZE, st_arr);


	// TODO 1 関連するst_arrが初期化されていなければ初期化する
	// TODO 2 find_new_lineを呼び出して改行があるかを確認する
	// TODO 3 改行があれば、行を返して、st_arrを更新する
	// TODO: 改行がなければread_fdを呼び出してデータを読み込む

	// TODO: static char**な変数を用意する　-> st_arr ファイルディスクリプたごとの配列
	// TODO: st_arr に改行があるか調べて、lineに入れたり、更新したりする
	

	return NULL;
}

int main(void)
{
/*
O_RDONLY	読み込み可
O_WRONLY	書き込み可
O_RDWR	読み書き可
*/
	int fd = open("test_line3.txt", O_RDONLY);
	char buffer[100];
	ssize_t bytes_read;
	
	while((bytes_read = read()))
}
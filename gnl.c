# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
#include <limits.h>
#include <libc.h>

# define BUFFER_SIZE 1

static char	*ft_strjoin(char *s1, char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*result;
	char	*dest;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_len = strlen(s1);
	s2_len = strlen(s2);
	result = (char *)malloc(sizeof(char) * s1_len + s2_len + 1);
	if (result == NULL)
		return (NULL);
	dest = result;
	memcpy(dest, s1, s1_len);
	memcpy(dest + s1_len, s2, s2_len);
	result[s1_len + s2_len] = '\0';
	return (result);
}

static char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*trim_s;
	size_t	s_len;
	size_t	i;

	if (s == NULL)
		return (NULL);
	i = 0;
	s_len = strlen(s);
	if (start >= s_len)
		return (strdup(""));
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

char	*get_next_line(int fd)
{
	static char	*save; //NULL
	char 		*buffer;
	char		*joined;
	ssize_t		read_bytes;

	if (save == NULL)
		joined = strdup("");
	else
		joined = strdup(save);
	read_bytes = 1;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	while (read_bytes > 0 && !strchr(joined, '\n')) // read関数からの読み込みが成功　かつ　joinedに改行文字が含まれていないとき
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		buffer[read_bytes] = '\0';
		joined = ft_strjoin(joined, buffer);
	}
	if (read_bytes == 0 && strlen(joined) == 0)
		return (NULL);

	char		*line;
	if (strchr(joined, '\n') == NULL)
	{
		line = strdup(joined);
		return (line);
	}
	else
	{
		int i = 0;
		while (joined[i] != '\n')
			i++;

		line = ft_substr(joined, 0, i + 1);
		save = strdup(joined + i + 1);
		return (line);
	}
}
// }

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

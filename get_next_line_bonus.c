/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozkan <seozkan@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 12:00:53 by seozkan           #+#    #+#             */
/*   Updated: 2022/12/19 13:12:28 by seozkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_get_line(char *left_str)
{
	size_t	i;
	char	*str;

	i = 0;
	if (!left_str[i])
		return (NULL);
	if (ft_strchr(left_str, '\n'))
		i = ft_strchr(left_str, '\n') - left_str + 1;
	else
		i = ft_strlen(left_str);
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, left_str, i + 1);
	return (str);
}

char	*ft_new_left_str(char *left_str)
{
	size_t	n_size;
	size_t	i;
	char	*str;

	if (!ft_strchr(left_str, '\n'))
	{
		free(left_str);
		return (NULL);
	}
	n_size = ft_strchr(left_str, '\n') - left_str;
	str = (char *)malloc(sizeof(char) * (ft_strlen(left_str) - n_size));
	if (!str)
		return (NULL);
	i = ft_strlen(left_str) - n_size;
	ft_strlcpy(str, left_str + n_size + 1, i);
	free(left_str);
	return (str);
}

//buffer size'a göre \n içeren bir parça olana kadar kopyalar
char	*ft_read_to_left_str(int fd, char *left_str)
{
	char	*buff;
	int		rd_bytes;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	rd_bytes = 1;
	while (!ft_strchr(left_str, '\n') && rd_bytes != 0)
	{
		rd_bytes = read(fd, buff, BUFFER_SIZE);
		if (rd_bytes == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[rd_bytes] = '\0';
		left_str = ft_strjoin(left_str, buff);
	}
	free(buff);
	return (left_str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*left_str[4096];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	left_str[fd] = ft_read_to_left_str(fd, left_str[fd]);
	if (!left_str[fd])
		return (NULL);
	line = ft_get_line(left_str[fd]);
	left_str[fd] = ft_new_left_str(left_str[fd]);
	return (line);
}

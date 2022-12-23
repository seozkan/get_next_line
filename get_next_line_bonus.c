/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozkan <seozkan@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 12:00:53 by seozkan           #+#    #+#             */
/*   Updated: 2022/12/23 19:43:21 by seozkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static	char	*new_str(char *str)
{
	char	*line;
	size_t	len;

	len = 0;
	while (str[len] && str[len] != '\n')
		len++;
	if (!str[len])
	{
		free (str);
		str = NULL;
		return (NULL);
	}
	line = (char *) malloc((ft_strlen(str) - len + 1) * sizeof(char));
	if (!line)
		return (NULL);
	ft_strlcpy(line, str + (len + 1), ft_strlen(str) - len + 1);
	free(str);
	str = NULL;
	return (line);
}

static	char	*get_line(char *str)
{
	size_t	len;
	char	*line;

	len = 0;
	if (!str[len])
		return (NULL);
	while (str[len] && str[len] != '\n')
		len++;
	line = (char *) malloc((len + 2) * sizeof(char));
	if (!line)
		return (NULL);
	ft_strlcpy(line, str, len + 2);
	return (line);
}

static	char	*read_file(int fd, char *str, char *buff)
{
	char	*tmp;
	ssize_t	rd_bytes;

	rd_bytes = 1;
	while (!ft_strchr(str, '\n') && rd_bytes != 0)
	{
		rd_bytes = read(fd, buff, BUFFER_SIZE);
		if (rd_bytes == -1)
		{
			free(buff);
			buff = NULL;
			free(str);
			return (NULL);
		}
		buff[rd_bytes] = '\0';
		tmp = str;
		str = ft_strjoin(str, buff);
		free(tmp);
		tmp = NULL;
	}
	free(buff);
	buff = NULL;
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str[4096];
	char		*line;
	char		*buff;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	if (!str[fd])
		str[fd] = ft_strdup("");
	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	str[fd] = read_file(fd, str[fd], buff);
	if (!str[fd])
		return (NULL);
	line = get_line(str[fd]);
	str[fd] = new_str(str[fd]);
	return (line);
}

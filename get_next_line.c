/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozkan <seozkan@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 13:56:37 by seozkan           #+#    #+#             */
/*   Updated: 2022/12/19 13:13:30 by seozkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

static	char	*read_file(int fd, char *str, char **buff)
{
	char	*tmp;
	ssize_t	bytes_read;

	bytes_read = 1;
	while (!ft_strchr(str, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, *buff, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(*buff);
			*buff = NULL;
			free(str);
			return (NULL);
		}
		(*buff)[bytes_read] = '\0';
		tmp = str;
		str = ft_strjoin(tmp, *buff);
		free(tmp);
		tmp = NULL;
	}
	free(*buff);
	*buff = NULL;
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str = NULL;
	char		*line;
	char		*buff;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	if (!str)
		str = ft_strdup("");
	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	str = read_file(fd, str, &buff);
	if (!str)
		return (NULL);
	line = get_line(str);
	str = new_str(str);
	return (line);
}

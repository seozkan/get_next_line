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

static	char	*new_backup(char *backup)
{
	char	*line;
	size_t	len;

	len = 0;
	while (backup[len] && backup[len] != '\n')
		len++;
	if (!backup[len])
	{
		free (backup);
		backup = NULL;
		return (NULL);
	}
	line = (char *) malloc((ft_strlen(backup) - len + 1) * sizeof(char));
	if (!line)
		return (NULL);
	ft_strlcpy(line, backup + (len + 1), ft_strlen(backup) - len + 1);
	free(backup);
	backup = NULL;
	return (line);
}

static	char	*get_line(char *backup)
{
	size_t	len;
	char	*line;

	len = 0;
	if (!backup[len])
		return (NULL);
	while (backup[len] && backup[len] != '\n')
		len++;
	line = (char *) malloc((len + 2) * sizeof(char));
	if (!line)
		return (NULL);
	ft_strlcpy(line, backup, len + 2);
	return (line);
}

static	char	*read_file(int fd, char *backup, char **buffer)
{
	char	*tmp;
	ssize_t	bytes_read;

	bytes_read = 1;
	while (!ft_strchr(backup, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, *buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free (backup);
			free (*buffer);
			*buffer = NULL;
			return (NULL);
		}
		(*buffer)[bytes_read] = '\0';
		tmp = backup;
		backup = ft_strjoin(tmp, *buffer);
		free(tmp);
		tmp = NULL;
	}
	free(*buffer);
	*buffer = NULL;
	return (backup);
}

char	*get_next_line(int fd)
{
	static char	*backup[4096];
	char		*line_return;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	if (!backup[fd])
		backup[fd] = ft_strdup("");
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	backup[fd] = read_file(fd, backup[fd], &buffer);
	if (!backup[fd])
		return (NULL);
	line_return = get_line(backup[fd]);
	backup[fd] = new_backup(backup[fd]);
	return (line_return);
}

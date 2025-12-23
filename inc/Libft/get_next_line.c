/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-der <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:17:17 by jvan-der          #+#    #+#             */
/*   Updated: 2025/09/09 15:33:36 by nvan-lae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*extract_line(char *buffer)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	if (!buffer || !*buffer)
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	j = -1;
	while (i > ++j)
		line[j] = buffer[j];
	line[j] = '\0';
	return (line);
}

static char	*clean_buffer(char *buffer)
{
	int		i;
	int		j;
	char	*new_buff;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	i++;
	new_buff = malloc (ft_strlen(buffer) - i + 1);
	if (!new_buff)
		return (NULL);
	while (buffer[i])
		new_buff[j++] = buffer[i++];
	new_buff[j] = '\0';
	free(buffer);
	return (new_buff);
}

static char	*read_and_store(int fd, char *buffer)
{
	char	*read_buffer;
	char	*temp;
	int		bytes;

	read_buffer = malloc(BUFFER_SIZE + 1);
	if (!read_buffer)
		return (NULL);
	bytes = 1;
	while (!ft_strchr(buffer, '\n') && bytes > 0)
	{
		bytes = read(fd, read_buffer, BUFFER_SIZE);
		if (bytes < 0)
		{
			free(read_buffer);
			return (NULL);
		}
		read_buffer[bytes] = '\0';
		temp = ft_strjoin(buffer, read_buffer);
		buffer = temp;
	}
	free(read_buffer);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd == -42)
	{
		if (buffer)
			free(buffer);
		buffer = NULL;
		return (NULL);
	}
	buffer = read_and_store(fd, buffer);
	if (!buffer)
		return (NULL);
	line = extract_line(buffer);
	buffer = clean_buffer(buffer);
	return (line);
}
/*

#include <fcntl.h>
#include <stdio.h>

int	main()
{
	int	fd;
	int	i = 0;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("error opening file");
		return (1);
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
		i++;
		printf("%d::::: %s", i, line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-lae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 11:54:52 by nvan-lae          #+#    #+#             */
/*   Updated: 2025/09/09 16:25:36 by nvan-lae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	validate_identifier(char **info)
{
	if (ft_strncmp(info[0], "A", 2) == 0)
		return (validate_a(info));
	else if (ft_strncmp(info[0], "C", 2) == 0)
		return (validate_c(info));
	else if (ft_strncmp(info[0], "L", 2) == 0)
		return (validate_l(info));
	else if (ft_strncmp(info[0], "sp", 3) == 0)
		return (validate_sp(info));
	else if (ft_strncmp(info[0], "pl", 3) == 0)
		return (validate_pl(info));
	else if (ft_strncmp(info[0], "cy", 3) == 0)
		return (validate_cy(info));
	else if (ft_strncmp(info[0], "pa", 3) == 0)
		return (validate_pa(info));
	return (error_msg("Wrong identifier"));
}

static char	*clean_line(char *line)
{
	char	*new_line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_line = ft_calloc(ft_strlen(line) + 1, sizeof(char));
	while (line[i] && (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'))
		i++;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
		{
			new_line[j++] = ' ';
			while (line[i] && (line[i] == ' ' || line[i] == '\t'
					|| line[i] == '\n'))
				i++;
		}
		else
			new_line[j++] = line[i++];
	}
	if (j > 0 && new_line[j - 1] == ' ')
		new_line[j - 1] = '\0';
	return (new_line);
}

static int	validate_line(char *line)
{
	char	**info;
	char	*cleaned_line;
	int		status;

	cleaned_line = clean_line(line);
	if (!cleaned_line || cleaned_line[0] == '\0' || cleaned_line[0] == '#')
	{
		free(cleaned_line);
		return (1);
	}
	info = ft_split(cleaned_line, ' ');
	free(cleaned_line);
	if (!info || !info[0])
	{
		if (info)
			free_array(info);
		return (1);
	}
	status = validate_identifier(info);
	free_array(info);
	return (status);
}

void	check_scene_file(const char *filename)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit("Error opening file\n");
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (!validate_line(line))
		{
			free(line);
			close(fd);
			error_exit("");
		}
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	close(fd);
}

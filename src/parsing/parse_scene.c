/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-der <jvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 00:00:00 by jvan-der          #+#    #+#             */
/*   Updated: 2025/08/20 15:28:45 by nvan-lae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	free_parts(char **p, int ret_val)
{
	int	i;

	i = 0;
	while (p[i])
		free(p[i++]);
	free(p);
	return (ret_val);
}

static int	parse_object(char *l, char **p, t_scene *s, t_count_objects *c)
{
	int	result;

	result = 1;
	if (ft_strcmp(p[0], "sp") == 0 && s->spheres
		&& c->sphere_idx < s->sphere_count)
		result = parse_sphere(l, &s->spheres[c->sphere_idx++], s->mlx);
	else if (ft_strcmp(p[0], "pl") == 0 && s->planes
		&& c->plane_idx < s->plane_count)
		result = parse_plane(l, &s->planes[c->plane_idx++], s->mlx);
	else if (ft_strcmp(p[0], "cy") == 0 && s->cylinders
		&& c->cylinder_idx < s->cylinder_count)
		result = parse_cylinder(l, &s->cylinders[c->cylinder_idx++], s->mlx);
	else if (ft_strcmp(p[0], "pa") == 0 && s->paraboloids
		&& c->paraboloid_idx < s->paraboloid_count)
		result = parse_paraboloid(l,
				&s->paraboloids[c->paraboloid_idx++], s->mlx);
	return (result);
}

static int	parse_line(char *line, t_scene *scene, t_count_objects *count)
{
	char	**parts;
	int		result;

	if (!line || line[0] == '\0' || line[0] == '#')
		return (1);
	parts = ft_split(line, ' ');
	if (!parts || !parts[0])
	{
		if (parts)
			free(parts);
		return (1);
	}
	result = 1;
	if (ft_strcmp(parts[0], "A") == 0)
		result = parse_ambient(line, &scene->ambient);
	else if (ft_strcmp(parts[0], "C") == 0 && scene->cameras
		&& count->camera_idx < scene->camera_count)
		result = parse_camera(line, &scene->cameras[count->camera_idx++]);
	else if (ft_strcmp(parts[0], "L") == 0 && scene->lights
		&& count->light_idx < scene->light_count)
		result = parse_light(line, &scene->lights[count->light_idx++]);
	else
		result = parse_object(line, parts, scene, count);
	return (free_parts(parts, result));
}

static int	read_and_parse_loop(int fd, t_scene *scene, t_count_objects *count)
{
	char	*line;
	int		len;

	line = get_next_line(fd);
	while (line != NULL)
	{
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		if (!parse_line(line, scene, count))
		{
			printf("Error parsing line: %s", line);
			free(line);
			return (0);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (1);
}

int	parse_scene(char *filename, t_scene *scene)
{
	int				fd;
	t_count_objects	count;
	int				status;

	count_objects(filename, &count);
	malloc_objects(scene, &count);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit("Error opening file");
	status = read_and_parse_loop(fd, scene, &count);
	close(fd);
	return (status);
}

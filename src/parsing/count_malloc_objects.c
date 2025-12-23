/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_malloc_objects.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-lae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 12:53:35 by nvan-lae          #+#    #+#             */
/*   Updated: 2025/08/15 13:09:27 by nvan-lae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	mini_count(char *line, t_count_objects *count)
{
	if (ft_strncmp(line, "sp ", 3) == 0)
		(count->sphere_count)++;
	else if (ft_strncmp(line, "pl ", 3) == 0)
		(count->plane_count)++;
	else if (ft_strncmp(line, "cy ", 3) == 0)
		(count->cylinder_count)++;
	else if (ft_strncmp(line, "pa ", 3) == 0)
		(count->paraboloid_count)++;
	else if (ft_strncmp(line, "L ", 2) == 0)
		(count->light_count)++;
	else if (ft_strncmp(line, "C ", 2) == 0)
		(count->camera_count)++;
}

void	count_objects(const char *filename, t_count_objects *count)
{
	int		fd;
	char	*line;

	objects_zero(count);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit("Error opening file for counting");
	line = get_next_line(fd);
	while (line != NULL)
	{
		mini_count(line, count);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

static void	sync_scene_count(t_scene *scene, t_count_objects *count)
{
	scene->sphere_count = count->sphere_count;
	scene->plane_count = count->plane_count;
	scene->cylinder_count = count->cylinder_count;
	scene->paraboloid_count = count->paraboloid_count;
	scene->light_count = count->light_count;
	scene->camera_count = count->camera_count;
}

void	malloc_objects(t_scene *scene, t_count_objects *count)
{
	scene->spheres = malloc(sizeof(t_sphere) * count->sphere_count);
	if (scene->spheres)
		ft_memset(scene->spheres, 0, sizeof(t_sphere) * count->sphere_count);
	scene->planes = malloc(sizeof(t_plane) * count->plane_count);
	if (scene->planes)
		ft_memset(scene->planes, 0, sizeof(t_plane) * count->plane_count);
	scene->cylinders = malloc(sizeof(t_cylinder) * count->cylinder_count);
	if (scene->cylinders)
		ft_memset(scene->cylinders, 0, sizeof(t_cylinder)
			* count->cylinder_count);
	scene->paraboloids = malloc(sizeof(t_paraboloid) * count->paraboloid_count);
	if (scene->paraboloids)
		ft_memset(scene->paraboloids, 0, sizeof(t_paraboloid)
			* count->paraboloid_count);
	scene->lights = malloc(sizeof(t_light) * count->light_count);
	if (scene->lights)
		ft_memset(scene->lights, 0, sizeof(t_light) * count->light_count);
	scene->cameras = malloc(sizeof(t_camera) * count->camera_count);
	if (scene->cameras)
		ft_memset(scene->cameras, 0, sizeof(t_camera) * count->camera_count);
	sync_scene_count(scene, count);
}

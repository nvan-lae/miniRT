/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-der <jvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 00:00:00 by jvan-der          #+#    #+#             */
/*   Updated: 2025/08/14 12:50:29 by nvan-lae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	parse_ambient(char *line, t_ambient *ambient)
{
	char	**parts;
	int		i;

	parts = ft_split(line, ' ');
	i = 0;
	if (!parts[1] || !parts[2])
		return (0);
	ambient->ratio = parse_double(parts[1]);
	ambient->color = parse_color(parts[2]);
	while (parts[i])
		free(parts[i++]);
	free(parts);
	return (1);
}

int	parse_camera(char *line, t_camera *camera)
{
	char	**parts;
	int		i;

	parts = ft_split(line, ' ');
	i = 0;
	if (!parts[1] || !parts[2] || !parts[3])
		return (0);
	camera->position = parse_vec3(parts[1], 0);
	camera->orientation = parse_vec3(parts[2], 1);
	camera->fov = parse_double(parts[3]);
	if (camera->fov < 0 || camera->fov > 180)
		error_exit("Camera FOV out of range (0-180)");
	while (parts[i])
		free(parts[i++]);
	free(parts);
	return (1);
}

int	parse_light(char *line, t_light *light)
{
	char	**parts;
	int		i;

	parts = ft_split(line, ' ');
	i = 0;
	if (!parts[1] || !parts[2] || !parts[3])
		return (0);
	light->position = parse_vec3(parts[1], 0);
	light->brightness = parse_double(parts[2]);
	light->color = parse_color(parts[3]);
	while (parts[i])
		free(parts[i++]);
	free(parts);
	return (1);
}

void	objects_zero(t_count_objects *count)
{
	count->sphere_count = 0;
	count->plane_count = 0;
	count->cylinder_count = 0;
	count->paraboloid_count = 0;
	count->light_count = 0;
	count->camera_count = 0;
	count->sphere_idx = 0;
	count->plane_idx = 0;
	count->cylinder_idx = 0;
	count->light_idx = 0;
	count->camera_idx = 0;
	count->paraboloid_idx = 0;
}

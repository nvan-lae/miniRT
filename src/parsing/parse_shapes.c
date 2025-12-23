/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shapes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-lae <nvan-lae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 10:18:35 by nvan-lae          #+#    #+#             */
/*   Updated: 2025/08/20 15:34:24 by nvan-lae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	parse_sphere(char *line, t_sphere *sphere, void *mlx)
{
	char	**parts;
	int		i;

	parts = ft_split(line, ' ');
	i = 0;
	if (!parts[1] || !parts[2] || !parts[3])
		return (0);
	sphere->center = parse_vec3(parts[1], 0);
	sphere->diameter = parse_double(parts[2]);
	sphere->color = parse_color(parts[3]);
	sphere->material = parse_material(parts, 4, mlx);
	while (parts[i])
		free(parts[i++]);
	free(parts);
	return (1);
}

int	parse_plane(char *line, t_plane *plane, void *mlx)
{
	char	**parts;
	int		i;

	parts = ft_split(line, ' ');
	i = 0;
	if (!parts[1] || !parts[2] || !parts[3])
		return (0);
	plane->point = parse_vec3(parts[1], 0);
	plane->normal = parse_vec3(parts[2], 1);
	plane->color = parse_color(parts[3]);
	plane->material = parse_material(parts, 4, mlx);
	while (parts[i])
		free(parts[i++]);
	free(parts);
	return (1);
}

int	parse_cylinder(char *line, t_cylinder *cylinder, void *mlx)
{
	char	**parts;
	int		i;

	parts = ft_split(line, ' ');
	i = 0;
	if (!parts[1] || !parts[2] || !parts[3] || !parts[4] || !parts[5])
		return (0);
	cylinder->center = parse_vec3(parts[1], 0);
	cylinder->axis = parse_vec3(parts[2], 1);
	cylinder->diameter = parse_double(parts[3]);
	cylinder->height = parse_double(parts[4]);
	cylinder->color = parse_color(parts[5]);
	cylinder->material = parse_material(parts, 6, mlx);
	while (parts[i])
		free(parts[i++]);
	free(parts);
	return (1);
}

int	parse_paraboloid(char *line, t_paraboloid *para, void *mlx)
{
	char	**parts;
	int		i;

	parts = ft_split(line, ' ');
	i = 0;
	if (!parts[1] || !parts[2] || !parts[3] || !parts[4] || !parts[5])
		return (0);
	para->vertex = parse_vec3(parts[1], 0);
	para->axis = parse_vec3(parts[2], 1);
	para->k = parse_double(parts[3]);
	para->height = parse_double(parts[4]);
	para->color = parse_color(parts[5]);
	para->material = parse_material(parts, 6, mlx);
	while (parts[i])
		free(parts[i++]);
	free(parts);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-lae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 12:27:32 by nvan-lae          #+#    #+#             */
/*   Updated: 2025/08/20 15:19:13 by nvan-lae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	free_spheres(t_scene *scene)
{
	int	i;

	if (scene->spheres)
	{
		i = 0;
		while (i < scene->sphere_count)
		{
			if (scene->spheres[i].material.bump_map.img)
				mlx_destroy_image(scene->mlx, \
					scene->spheres[i].material.bump_map.img);
			i++;
		}
		free(scene->spheres);
	}
}

static void	free_planes(t_scene *scene)
{
	int	i;

	if (scene->planes)
	{
		i = 0;
		while (i < scene->plane_count)
		{
			if (scene->planes[i].material.bump_map.img)
				mlx_destroy_image(scene->mlx, \
					scene->planes[i].material.bump_map.img);
			i++;
		}
		free(scene->planes);
	}
}

static void	free_cylinders(t_scene *scene)
{
	int	i;

	if (scene->cylinders)
	{
		i = 0;
		while (i < scene->cylinder_count)
		{
			if (scene->cylinders[i].material.bump_map.img)
				mlx_destroy_image(scene->mlx, \
					scene->cylinders[i].material.bump_map.img);
			i++;
		}
		free(scene->cylinders);
	}
}

static void	free_paraboloids(t_scene *scene)
{
	int	i;

	if (scene->paraboloids)
	{
		i = 0;
		while (i < scene->paraboloid_count)
		{
			if (scene->paraboloids[i].material.bump_map.img)
				mlx_destroy_image(scene->mlx, \
					scene->paraboloids[i].material.bump_map.img);
			i++;
		}
		free(scene->paraboloids);
	}
}

void	free_scene(t_scene *scene)
{
	if (scene->cameras)
		free(scene->cameras);
	if (scene->lights)
		free(scene->lights);
	free_spheres(scene);
	free_planes(scene);
	free_cylinders(scene);
	free_paraboloids(scene);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-lae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 13:48:44 by nvan-lae          #+#    #+#             */
/*   Updated: 2025/09/03 13:48:54 by nvan-lae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	shadow_hits_sphere(t_ray shadow_ray, t_scene *scene, double light_dist)
{
	double	t_shadow;
	int		j;

	j = -1;
	while (++j < scene->sphere_count)
	{
		if (ray_sphere_intersection(shadow_ray, scene->spheres[j], &t_shadow)
			&& t_shadow > 1e-6 && t_shadow < light_dist)
			return (1);
	}
	return (0);
}

int	shadow_hits_plane(t_ray shadow_ray, t_scene *scene, double light_dist)
{
	double	t_shadow;
	int		j;

	j = -1;
	while (++j < scene->plane_count)
	{
		if (ray_plane_intersection(shadow_ray, scene->planes[j], &t_shadow)
			&& t_shadow > 1e-6 && t_shadow < light_dist)
			return (1);
	}
	return (0);
}

int	shadow_hits_cylinder(t_ray shadow_ray, t_scene *scene, double light_dist)
{
	double	t_shadow;
	int		j;

	j = -1;
	while (++j < scene->cylinder_count)
	{
		if (ray_cylinder_intersection(shadow_ray, scene->cylinders[j],
				&t_shadow) && t_shadow > 1e-6 && t_shadow < light_dist)
			return (1);
	}
	return (0);
}

int	shadow_hits_paraboloid(t_ray shadow_ray, t_scene *scene,
							double light_dist)
{
	double	t_shadow;
	int		j;

	j = -1;
	while (++j < scene->paraboloid_count)
	{
		if (ray_paraboloid_intersection(shadow_ray,
				scene->paraboloids[j], &t_shadow)
			&& t_shadow > 1e-6 && t_shadow < light_dist)
			return (1);
	}
	return (0);
}

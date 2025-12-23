/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-der <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 14:18:40 by jvan-der          #+#    #+#             */
/*   Updated: 2025/09/03 10:38:28 by nvan-lae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3	get_normal_plane(t_hit hit)
{
	t_plane	*pl;

	pl = (t_plane *)hit.object;
	return (vec3_normalize(pl->normal));
}

void	find_closest_object_plane(t_ray ray, t_scene *scene, t_hit *closest)
{
	double	t;
	int		i;

	i = -1;
	while (++i < scene->plane_count)
	{
		if (ray_plane_intersection(ray, scene->planes[i], &t))
		{
			if (t > 1e-6 && t < closest->t)
			{
				closest->type = OBJ_PLANE;
				closest->object = &scene->planes[i];
				closest->t = t;
			}
		}
	}
}

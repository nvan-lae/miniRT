/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-der <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 14:12:16 by jvan-der          #+#    #+#             */
/*   Updated: 2025/09/03 10:39:15 by nvan-lae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3	get_normal_sphere(t_hit hit, t_ray ray)
{
	t_sphere	*s;
	t_vec3		p;

	s = (t_sphere *)hit.object;
	p = get_hit_point(ray, hit.t);
	return (vec3_normalize(vec3_sub(p, s->center)));
}

void	find_closest_object_sphere(t_ray ray, t_scene *scene, t_hit *closest)
{
	double	t;
	int		i;

	i = -1;
	while (++i < scene->sphere_count)
	{
		if (ray_sphere_intersection(ray, scene->spheres[i], &t))
		{
			if (t > 1e-6 && t < closest->t)
			{
				closest->type = OBJ_SPHERE;
				closest->object = &scene->spheres[i];
				closest->t = t;
			}
		}
	}
}

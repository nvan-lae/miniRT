/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-der <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 14:15:26 by jvan-der          #+#    #+#             */
/*   Updated: 2025/09/03 10:31:16 by nvan-lae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3	get_normal_cylinder(t_hit hit, t_ray ray)
{
	t_cylinder	*cy;
	t_vec3		p;
	t_vec3		axis;
	t_vec3		cp;
	double		proj;

	cy = (t_cylinder *)hit.object;
	p = get_hit_point(ray, hit.t);
	axis = vec3_normalize(cy->axis);
	cp = vec3_sub(p, cy->center);
	proj = vec3_dot(cp, axis);
	if (fabs(proj - cy->height / 2.0) < 1e-6)
		return (axis);
	else if (fabs(proj + cy->height / 2.0) < 1e-6)
		return (vec3_mult(axis, -1));
	return (vec3_normalize(vec3_sub(cp, vec3_mult(axis, proj))));
}

void	find_closest_object_cylinder(t_ray ray, t_scene *scene, t_hit *closest)
{
	double	t;
	int		i;

	i = -1;
	while (++i < scene->cylinder_count)
	{
		if (ray_cylinder_intersection(ray, scene->cylinders[i], &t))
		{
			if (t > 1e-6 && t < closest->t)
			{
				closest->type = OBJ_CYLINDER;
				closest->object = &scene->cylinders[i];
				closest->t = t;
			}
		}
	}
}

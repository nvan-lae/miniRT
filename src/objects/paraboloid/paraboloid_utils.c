/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paraboloid_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-der <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 14:21:27 by jvan-der          #+#    #+#             */
/*   Updated: 2025/09/03 10:35:58 by nvan-lae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3	get_normal_paraboloid(t_hit hit, t_ray ray)
{
	t_paraboloid	*pa;
	t_vec3			hit_point;
	t_vec3			oc;
	double			m;
	t_vec3			normal;

	pa = (t_paraboloid *)hit.object;
	hit_point = get_hit_point(ray, hit.t);
	oc = vec3_sub(hit_point, pa->vertex);
	m = vec3_dot(oc, pa->axis);
	normal = vec3_sub(oc, vec3_mult(pa->axis, m + pa->k / 2.0));
	return (vec3_normalize(normal));
}

void	find_closest_object_paraboloid(t_ray r, t_scene *s, t_hit *c)
{
	double	t;
	int		i;

	i = -1;
	while (++i < s->paraboloid_count)
	{
		if (ray_paraboloid_intersection(r, s->paraboloids[i], &t))
		{
			if (t > 1e-6 && t < c->t)
			{
				c->type = OBJ_PARABOLOID;
				c->object = &s->paraboloids[i];
				c->t = t;
			}
		}
	}
}

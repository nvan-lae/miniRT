/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-lae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 13:05:51 by nvan-lae          #+#    #+#             */
/*   Updated: 2025/09/03 13:06:11 by nvan-lae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3	get_hit_point(t_ray ray, double t)
{
	return (vec3_add(ray.origin, vec3_mult(ray.direction, t)));
}

t_vec3	get_normal(t_hit hit, t_ray ray)
{
	if (hit.type == OBJ_SPHERE)
		return (get_normal_sphere(hit, ray));
	else if (hit.type == OBJ_PLANE)
		return (get_normal_plane(hit));
	else if (hit.type == OBJ_CYLINDER)
		return (get_normal_cylinder(hit, ray));
	else if (hit.type == OBJ_PARABOLOID)
		return (get_normal_paraboloid(hit, ray));
	return ((t_vec3){0, 1, 0});
}

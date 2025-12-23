/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-lae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:17:10 by nvan-lae          #+#    #+#             */
/*   Updated: 2025/09/03 11:56:22 by nvan-lae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	ray_sphere_intersection(t_ray ray, t_sphere sphere, double *t)
{
	t_vec3	oc;
	double	a;
	double	b;
	double	c;
	double	discriminant;

	oc = vec3_sub(ray.origin, sphere.center);
	a = vec3_dot(ray.direction, ray.direction);
	b = 2.0 * vec3_dot(oc, ray.direction);
	c = vec3_dot(oc, oc) - (sphere.diameter / 2.0) * (sphere.diameter / 2.0);
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (0);
	*t = (-b - sqrt(discriminant)) / (2.0 * a);
	if (*t > 1e-6)
		return (1);
	*t = (-b + sqrt(discriminant)) / (2.0 * a);
	if (*t > 1e-6)
		return (1);
	return (0);
}

int	ray_plane_intersection(t_ray ray, t_plane plane, double *t)
{
	double	denom;
	t_vec3	p0l0;

	denom = vec3_dot(plane.normal, ray.direction);
	if (fabs(denom) < 1e-6)
		return (0);
	p0l0 = vec3_sub(plane.point, ray.origin);
	*t = vec3_dot(p0l0, plane.normal) / denom;
	if (*t < 1e-6)
		return (0);
	return (1);
}

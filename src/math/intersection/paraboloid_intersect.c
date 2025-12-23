/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paraboloid_intersect.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-lae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 11:58:24 by nvan-lae          #+#    #+#             */
/*   Updated: 2025/09/09 17:45:47 by nvan-lae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	check_paraboloid_hit(t_ray ray, t_paraboloid pa, double t_val)
{
	double	proj;
	t_vec3	hit_point;

	if (t_val <= 1e-6)
		return (0);
	hit_point = get_hit_point(ray, t_val);
	proj = vec3_dot(vec3_sub(hit_point, pa.vertex), pa.axis);
	if (proj >= 0 && proj <= pa.height)
		return (1);
	return (0);
}

static double	find_closest_valid_hit(t_ray r, t_paraboloid pa,
									double t0, double t1)
{
	int	hit_t0;
	int	hit_t1;

	hit_t0 = check_paraboloid_hit(r, pa, t0);
	hit_t1 = check_paraboloid_hit(r, pa, t1);
	if (hit_t0 && (!hit_t1 || t0 < t1))
		return (t0);
	if (hit_t1)
		return (t1);
	return (0);
}

int	ray_paraboloid_intersection(t_ray ray, t_paraboloid pa, double *t)
{
	t_vec3	oc;
	double	a;
	double	b;
	double	c;
	double	discriminant;

	oc = vec3_sub(ray.origin, pa.vertex);
	a = vec3_dot(ray.direction, ray.direction)
		- pow(vec3_dot(ray.direction, pa.axis), 2);
	b = 2 * (vec3_dot(ray.direction, oc)
			- vec3_dot(ray.direction, pa.axis) * vec3_dot(oc, pa.axis))
		- pa.k * vec3_dot(ray.direction, pa.axis);
	c = vec3_dot(oc, oc) - pow(vec3_dot(oc, pa.axis), 2)
		- pa.k * vec3_dot(oc, pa.axis);
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (0);
	*t = find_closest_valid_hit(ray, pa,
			(-b - sqrt(discriminant)) / (2 * a),
			(-b + sqrt(discriminant)) / (2 * a));
	if (*t > 1e-6)
		return (1);
	return (0);
}

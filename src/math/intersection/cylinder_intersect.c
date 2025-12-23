/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-lae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 11:57:24 by nvan-lae          #+#    #+#             */
/*   Updated: 2025/09/03 12:15:16 by nvan-lae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	calculate_body_coeffs(t_ray ray, t_cylinder cy, double *coeffs)
{
	t_vec3	oc;

	oc = vec3_sub(ray.origin, cy.center);
	coeffs[0] = vec3_dot(ray.direction, ray.direction)
		- pow(vec3_dot(ray.direction, cy.axis), 2);
	coeffs[1] = 2 * (vec3_dot(ray.direction, oc)
			- vec3_dot(ray.direction, cy.axis) * vec3_dot(oc, cy.axis));
	coeffs[2] = vec3_dot(oc, oc) - pow(vec3_dot(oc, cy.axis), 2)
		- (cy.diameter / 2.0) * (cy.diameter / 2.0);
}

static double	get_valid_body_t(t_ray ray, t_cylinder cy, double t)
{
	double	proj;

	if (t > 1e-6)
	{
		proj = vec3_dot(vec3_sub(get_hit_point(ray, t), cy.center), cy.axis);
		if (proj >= -cy.height / 2.0 && proj <= cy.height / 2.0)
			return (t);
	}
	return (1e30);
}

static int	intersect_cylinder_body(t_ray ray, t_cylinder cy, double *t)
{
	double	coeffs[3];
	double	discriminant;
	double	t0;
	double	t1;

	calculate_body_coeffs(ray, cy, coeffs);
	discriminant = coeffs[1] * coeffs[1] - 4 * coeffs[0] * coeffs[2];
	if (discriminant < 0)
		return (0);
	t0 = (-coeffs[1] - sqrt(discriminant)) / (2.0 * coeffs[0]);
	t1 = (-coeffs[1] + sqrt(discriminant)) / (2.0 * coeffs[0]);
	t0 = get_valid_body_t(ray, cy, t0);
	t1 = get_valid_body_t(ray, cy, t1);
	*t = fmin(t0, t1);
	if (*t >= 1e30)
		return (0);
	return (1);
}

static void	check_single_cap(t_ray ray, t_cylinder cy, double *t, int is_top)
{
	t_plane	cap_plane;
	double	t_intersect;

	if (is_top)
	{
		cap_plane.point = vec3_add(cy.center,
				vec3_mult(cy.axis, cy.height / 2.0));
		cap_plane.normal = cy.axis;
	}
	else
	{
		cap_plane.point = vec3_sub(cy.center,
				vec3_mult(cy.axis, cy.height / 2.0));
		cap_plane.normal = vec3_mult(cy.axis, -1);
	}
	if (ray_plane_intersection(ray, cap_plane, &t_intersect))
	{
		if (t_intersect > 1e-6 && t_intersect < *t)
		{
			if (vec3_length(vec3_sub(get_hit_point(ray, t_intersect),
						cap_plane.point)) <= cy.diameter / 2.0)
				*t = t_intersect;
		}
	}
}

int	ray_cylinder_intersection(t_ray ray, t_cylinder cylinder, double *t)
{
	double	t_side;
	double	t_caps;
	int		hit_side;
	int		hit_caps;

	t_side = 1e30;
	t_caps = 1e30;
	hit_side = intersect_cylinder_body(ray, cylinder, &t_side);
	check_single_cap(ray, cylinder, &t_caps, 1);
	check_single_cap(ray, cylinder, &t_caps, 0);
	hit_caps = (t_caps < 1e30);
	if (!hit_side && !hit_caps)
		return (0);
	if (t_side < t_caps)
		*t = t_side;
	else
		*t = t_caps;
	return (1);
}

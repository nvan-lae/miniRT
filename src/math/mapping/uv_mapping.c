/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_mapping.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-lae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 17:12:08 by nvan-lae          #+#    #+#             */
/*   Updated: 2025/08/15 12:25:08 by nvan-lae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	get_sphere_uv(t_vec3 p, double *u, double *v)
{
	double	phi;
	double	theta;

	phi = atan2(p.z, p.x);
	theta = acos(p.y);
	*u = 1 - (phi + M_PI) / (2 * M_PI);
	*v = 1 - theta / M_PI;
}

void	get_plane_uv(t_vec3 p, t_vec3 normal, double *u, double *v)
{
	t_vec3	u_axis;
	t_vec3	v_axis;

	if (fabs(normal.y) > 0.99)
		u_axis = (t_vec3){1, 0, 0};
	else
		u_axis = vec3_normalize(vec3_cross((t_vec3){0, 1, 0}, normal));
	v_axis = vec3_normalize(vec3_cross(normal, u_axis));
	*u = fmod(vec3_dot(p, u_axis) * 0.1, 1.0);
	*v = fmod(vec3_dot(p, v_axis) * 0.1, 1.0);
	if (*u < 0)
		*u += 1.0;
	if (*v < 0)
		*v += 1.0;
}

void	get_object_uv(t_hit hit, t_vec3 hit_point, double *u, double *v)
{
	t_sphere	*sp;
	t_vec3		p_local;
	t_plane		*pl;

	if (hit.type == OBJ_SPHERE)
	{
		sp = (t_sphere *)hit.object;
		p_local = vec3_normalize(vec3_sub(hit_point, sp->center));
		get_sphere_uv(p_local, u, v);
	}
	else if (hit.type == OBJ_PLANE)
	{
		pl = (t_plane *)hit.object;
		get_plane_uv(hit_point, pl->normal, u, v);
	}
	else
	{
		*u = 0;
		*v = 0;
	}
}

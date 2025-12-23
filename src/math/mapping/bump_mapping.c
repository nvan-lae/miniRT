/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_mapping.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-lae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 10:41:40 by nvan-lae          #+#    #+#             */
/*   Updated: 2025/09/03 11:12:01 by nvan-lae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
** Computes the perturbed normal for bump mapping.
*/

static t_vec3	get_map_normal(t_hit hit, t_vec3 hit_point, t_material mat)
{
	double	u;
	double	v;
	int		x;
	int		y;
	int		color;

	get_object_uv(hit, hit_point, &u, &v);
	x = (int)(u * (mat.bump_map.width - 1));
	y = (int)(v * (mat.bump_map.height - 1));
	color = *(unsigned int *)(mat.bump_map.addr + (y
				* mat.bump_map.line_length + x
				* (mat.bump_map.bits_per_pixel / 8)));
	return ((t_vec3){
		((color >> 16) & 0xFF) / 255.0 * 2.0 - 1.0,
		((color >> 8) & 0xFF) / 255.0 * 2.0 - 1.0,
		(color & 0xFF) / 255.0 * 2.0 - 1.0});
}

static void	create_tbn_space(t_vec3 normal, t_vec3 *tangent, t_vec3 *bitangent)
{
	if (fabs(normal.y) > 0.99)
		*tangent = vec3_normalize(vec3_cross(normal, (t_vec3){0, 0, 1}));
	else
		*tangent = vec3_normalize(vec3_cross(normal, (t_vec3){0, 1, 0}));
	*bitangent = vec3_normalize(vec3_cross(normal, *tangent));
}

t_vec3	get_bump_normal(t_hit hit, t_vec3 hit_point,
						t_vec3 normal, t_material mat)
{
	t_vec3	map_normal;
	t_vec3	tangent;
	t_vec3	bitangent;
	t_vec3	result;

	map_normal = get_map_normal(hit, hit_point, mat);
	create_tbn_space(normal, &tangent, &bitangent);
	result = vec3_mult(tangent, map_normal.x);
	result = vec3_add(result, vec3_mult(bitangent, map_normal.y));
	result = vec3_add(result, vec3_mult(normal, map_normal.z));
	return (vec3_normalize(result));
}

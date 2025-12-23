/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-lae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 13:29:02 by nvan-lae          #+#    #+#             */
/*   Updated: 2025/09/03 13:29:24 by nvan-lae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * @brief Retrieves the material properties of the object that was hit.
 * @param closest A pointer to the t_hit struct containing hit information.
 * @return The t_material struct for the hit object.
 */
t_material	get_material(t_hit *closest)
{
	if (closest->type == OBJ_SPHERE)
		return (((t_sphere *)closest->object)->material);
	else if (closest->type == OBJ_PLANE)
		return (((t_plane *)closest->object)->material);
	else if (closest->type == OBJ_CYLINDER)
		return (((t_cylinder *)closest->object)->material);
	else if (closest->type == OBJ_PARABOLOID)
		return (((t_paraboloid *)closest->object)->material);
	return ((t_material){MAT_DIFFUSE, 0, 0, 1.0, TEX_NONE, {0, 0, 0}, {0}});
}

/**
 * @brief Gets the base color of an object and applies textures if any.
 * @param closest The t_hit struct for the intersected object.
 * @param hit_point The 3D coordinate of the intersection point.
 * @return The final base color after applying textures like checkerboards.
 */
t_color	get_textured_color(t_hit *closest, t_vec3 hit_point)
{
	t_color		base_color;
	t_material	mat;
	double		u;
	double		v;
	int			pattern;

	mat = get_material(closest);
	if (closest->type == OBJ_SPHERE)
		base_color = ((t_sphere *)closest->object)->color;
	else if (closest->type == OBJ_PLANE)
		base_color = ((t_plane *)closest->object)->color;
	else if (closest->type == OBJ_CYLINDER)
		base_color = ((t_cylinder *)closest->object)->color;
	else
		base_color = ((t_paraboloid *)closest->object)->color;
	if (mat.texture_type == TEX_CHECKER)
	{
		get_object_uv(*closest, hit_point, &u, &v);
		pattern = (int)(floor(u * 10) + floor(v * 10)) % 2;
		if (pattern != 0)
			base_color = mat.color2;
	}
	return (base_color);
}

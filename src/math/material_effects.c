/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material_effects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-lae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 13:30:33 by nvan-lae          #+#    #+#             */
/*   Updated: 2025/09/03 13:30:44 by nvan-lae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * @brief Calculates the color contribution from reflection.
 * @param info A struct containing all necessary hit and scene information.
 * @return The integer color value seen in the reflection.
 */
static int	get_reflection_color(t_hit_info *info)
{
	t_ray	reflect_ray;

	reflect_ray.direction = vec3_sub(info->ray.direction,
			vec3_mult(info->normal, 2 * vec3_dot(info->ray.direction,
					info->normal)));
	reflect_ray.direction = vec3_normalize(reflect_ray.direction);
	reflect_ray.origin = vec3_add(info->hit_point,
			vec3_mult(info->normal, 1e-4));
	return (trace_ray(reflect_ray, info->scene, info->depth + 1));
}

/**
 * @brief Calculates the color contribution from refraction.
 * @param info A struct containing all necessary hit and scene information.
 * @return The integer color value seen through the transparent material.
 */
static int	get_refraction_color(t_hit_info *info)
{
	t_ray	refract_ray;
	double	ior;

	ior = info->mat.ior;
	if (ior <= 0)
		ior = 1.5;
	refract_ray.direction = refract(info->ray.direction, info->normal, ior);
	if (vec3_length(refract_ray.direction) < 1e-6)
		return (0);
	refract_ray.direction = vec3_normalize(refract_ray.direction);
	refract_ray.origin = vec3_sub(info->hit_point,
			vec3_mult(info->normal, 1e-4));
	return (trace_ray(refract_ray, info->scene, info->depth + 1));
}

/**
 * @brief Blends two colors based on a reflection ratio.
 * @param base_color The object's own color.
 * @param reflected_color The color from the reflection.
 * @param ratio The blend factor (0.0 to 1.0).
 * @return The final blended t_color.
 */
static t_color	blend_reflection(t_color base, int reflected, double ratio)
{
	t_color	final;

	final.r = (1.0 - ratio) * base.r + ratio * ((reflected >> 16) & 0xFF);
	final.g = (1.0 - ratio) * base.g + ratio * ((reflected >> 8) & 0xFF);
	final.b = (1.0 - ratio) * base.b + ratio * (reflected & 0xFF);
	return (final);
}

/**
 * @brief Blends reflected and refracted colors using the Fresnel effect.
 * @param reflected_color The color from reflection.
 * @param refracted_color The color from refraction.
 * @param kr The Fresnel coefficient (reflection amount).
 * @return The final blended t_color.
 */
static t_color	blend_fresnel(int reflected, int refracted, double kr)
{
	t_color	final;

	final.r = kr * ((reflected >> 16) & 0xFF)
		+ (1.0 - kr) * ((refracted >> 16) & 0xFF);
	final.g = kr * ((reflected >> 8) & 0xFF)
		+ (1.0 - kr) * ((refracted >> 8) & 0xFF);
	final.b = kr * (reflected & 0xFF)
		+ (1.0 - kr) * (refracted & 0xFF);
	return (final);
}

/**
 * @brief Calculates the final color for reflective or transparent materials.
 * @param ray The incoming ray that hit the object.
 * @param scene The scene containing lights and objects.
 * @param closest The hit information for the intersection.
 * @param depth The current recursion depth.
 * @return The final computed t_color for the material.
 */
t_color	calculate_material_effects(t_ray ray, t_scene *scene,
									t_hit closest, int depth)
{
	t_hit_info	info;
	int			reflected_color;
	int			refracted_color;
	double		kr;

	info.ray = ray;
	info.scene = scene;
	info.depth = depth;
	info.mat = get_material(&closest);
	info.hit_point = get_hit_point(ray, closest.t);
	info.normal = get_normal(closest, ray);
	if (info.mat.type == MAT_MIRROR)
	{
		reflected_color = get_reflection_color(&info);
		info.base_color = get_textured_color(&closest, info.hit_point);
		return (blend_reflection(info.base_color, reflected_color,
				info.mat.reflection));
	}
	reflected_color = get_reflection_color(&info);
	kr = fresnel(info.ray.direction, info.normal, info.mat.ior);
	if (kr >= 1.0)
		return (blend_fresnel(reflected_color, 0, 1.0));
	refracted_color = get_refraction_color(&info);
	return (blend_fresnel(reflected_color, refracted_color, kr));
}

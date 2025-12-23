/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-lae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 13:29:38 by nvan-lae          #+#    #+#             */
/*   Updated: 2025/09/03 13:47:39 by nvan-lae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * @brief Checks if a shadow ray is blocked by any object in the scene. This
 * function delegates the checks for each object type to specialized helpers.
 * @return 1 if the point is in shadow, 0 otherwise.
 */
static int	is_in_shadow(t_ray shadow_ray, t_scene *scene, double light_dist)
{
	if (shadow_hits_sphere(shadow_ray, scene, light_dist))
		return (1);
	if (shadow_hits_plane(shadow_ray, scene, light_dist))
		return (1);
	if (shadow_hits_cylinder(shadow_ray, scene, light_dist))
		return (1);
	if (shadow_hits_paraboloid(shadow_ray, scene, light_dist))
		return (1);
	return (0);
}

/**
 * @brief Calculates the diffuse lighting for a single light source,
 * checking for shadows first.
 * @return The diffuse color contribution from this specific light.
 */
static t_color	get_diffuse_for_light(t_light *light, t_hit_info *info)
{
	t_color	diffuse_color;
	t_ray	shadow_ray;
	double	light_dist;
	double	diff;

	diffuse_color = (t_color){0, 0, 0};
	shadow_ray.direction = vec3_normalize(vec3_sub(light->position,
				info->hit_point));
	shadow_ray.origin = vec3_add(info->hit_point,
			vec3_mult(info->normal, 1e-4));
	light_dist = vec3_length(vec3_sub(light->position, info->hit_point));
	if (is_in_shadow(shadow_ray, info->scene, light_dist))
		return (diffuse_color);
	diff = fmax(0.0, vec3_dot(info->normal, shadow_ray.direction));
	diffuse_color.r = (int)(info->base_color.r * light->color.r / 255.0
			* light->brightness * diff);
	diffuse_color.g = (int)(info->base_color.g * light->color.g / 255.0
			* light->brightness * diff);
	diffuse_color.b = (int)(info->base_color.b * light->color.b / 255.0
			* light->brightness * diff);
	return (diffuse_color);
}

/**
 * @brief Initializes the hit_info struct with all necessary data for lighting
 * calculations, including applying bump maps to the normal.
 */
static void	init_lighting_info(t_hit_info *info, t_ray ray, t_scene *scene,
								t_hit closest)
{
	info->hit_point = get_hit_point(ray, closest.t);
	info->base_color = get_textured_color(&closest, info->hit_point);
	info->normal = get_normal(closest, ray);
	info->scene = scene;
	if (get_material(&closest).texture_type == TEX_BUMPMAP)
		info->normal = get_bump_normal(closest, info->hit_point, info->normal,
				get_material(&closest));
}

/**
 * @brief Sums the diffuse lighting contributions from all light sources.
 * @return The total diffuse color accumulated from all lights.
 */
static t_color	sum_diffuse_lighting(t_hit_info *info)
{
	t_color	total_diffuse;
	t_color	diffuse_from_light;
	int		i;

	total_diffuse = (t_color){0, 0, 0};
	i = -1;
	while (++i < info->scene->light_count)
	{
		diffuse_from_light = get_diffuse_for_light(
				&info->scene->lights[i], info);
		total_diffuse.r += diffuse_from_light.r;
		total_diffuse.g += diffuse_from_light.g;
		total_diffuse.b += diffuse_from_light.b;
	}
	return (total_diffuse);
}

/**
 * @brief Calculates the total color for a point on a diffuse surface by
 * combining ambient and diffuse lighting from all sources.
 */
t_color	calculate_lighting(t_ray ray, t_scene *scene, t_hit closest)
{
	t_hit_info	info;
	t_color		total_diffuse;
	t_color		final_color;

	init_lighting_info(&info, ray, scene, closest);
	total_diffuse = sum_diffuse_lighting(&info);
	final_color = apply_ambient(info.base_color, scene->ambient);
	final_color.r = fmin(255, final_color.r + total_diffuse.r);
	final_color.g = fmin(255, final_color.g + total_diffuse.g);
	final_color.b = fmin(255, final_color.b + total_diffuse.b);
	return (final_color);
}

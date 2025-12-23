/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-lae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 13:22:50 by nvan-lae          #+#    #+#             */
/*   Updated: 2025/09/03 15:00:48 by nvan-lae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * @brief Finds the closest object that intersects with a given ray.
 * @param ray The ray to test for intersections.
 * @param scene The scene containing all objects.
 * @param closest A pointer to a t_hit struct that will store information
 * about the closest intersection found.
 */
static void	find_closest_object(t_ray ray, t_scene *scene, t_hit *closest)
{
	closest->type = OBJ_NONE;
	closest->object = NULL;
	closest->t = 1e30;
	find_closest_object_sphere(ray, scene, closest);
	find_closest_object_plane(ray, scene, closest);
	find_closest_object_cylinder(ray, scene, closest);
	find_closest_object_paraboloid(ray, scene, closest);
}

/**
 * @brief Computes the final color of a pixel by tracing a ray into the scene.
 * @param ray The primary ray cast from the camera.
 * @param scene The scene to be rendered.
 * @param depth The current recursion depth (for reflections/refractions).
 * @return The final integer color value for the pixel.
 * @note This is the main recursive function of the ray tracer. It finds a hit,
 * then calculates the color based on lighting, shadows, and material effects
 * like reflection and refraction, calling other specialized functions to do so.
 */
int	trace_ray(t_ray ray, t_scene *scene, int depth)
{
	t_hit		closest;
	t_color		final_color;
	t_material	mat;

	if (depth > 5)
		return (0x000000);
	find_closest_object(ray, scene, &closest);
	if (closest.type == OBJ_NONE)
		return (0x000000);
	mat = get_material(&closest);
	if (mat.type == MAT_MIRROR || mat.type == MAT_GLASS)
		final_color = calculate_material_effects(ray, scene, closest, depth);
	else
		final_color = calculate_lighting(ray, scene, closest);
	return (create_rgb(final_color.r, final_color.g, final_color.b));
}

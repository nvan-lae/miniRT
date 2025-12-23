/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_math.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-der <jvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 00:00:00 by jvan-der          #+#    #+#             */
/*   Updated: 2025/09/03 13:18:54 by nvan-lae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * @brief Establishes the camera's local coordinate system (basis vectors).
 * @param cam The camera being used.
 * @param forward Pointer to store the camera's forward-facing vector.
 * @param right Pointer to store the camera's right-facing vector.
 * @param up Pointer to store the camera's up-facing vector.
 * @note This handles the "gimbal lock" problem by choosing a different "up"
 * vector when the camera looks straight up or down.
 */
static void	setup_camera_basis(t_camera *cam, t_vec3 *fwd, t_vec3 *r, t_vec3 *u)
{
	t_vec3	world_up;

	*fwd = vec3_normalize(cam->orientation);
	world_up = (t_vec3){0, 1, 0};
	if (fabs(fwd->x) < 1e-6 && fabs(fwd->z) < 1e-6)
	{
		if (fwd->y > 0)
			world_up = (t_vec3){0, 0, -1};
		else
			world_up = (t_vec3){0, 0, 1};
	}
	*r = vec3_normalize(vec3_cross(world_up, *fwd));
	*u = vec3_normalize(vec3_cross(*fwd, *r));
}

/**
 * @brief Calculates a pixel's coordinates on the camera's virtual view plane.
 * @param cam The camera containing FOV and aspect ratio settings.
 * @param x The pixel's horizontal screen coordinate.
 * @param y The pixel's vertical screen coordinate.
 * @return A t_vec3 containing the (x, y) offsets on the view plane.
 * @note This converts the 2D integer pixel coordinates (e.g., 100, 150) into
 * 3D floating-point coordinates relative to the center of the camera's view.
 */
static t_vec3	calculate_pixel_on_plane(t_camera *cam, int x, int y)
{
	double	aspect_ratio;
	double	fov_tan;
	t_vec3	pixel_offset;

	aspect_ratio = (double)WIDTH / (double)HEIGHT;
	fov_tan = tan(cam->fov * M_PI / 180.0 / 2.0);
	pixel_offset.x = (2 * (x + 0.5) / (double)WIDTH - 1)
		* aspect_ratio * fov_tan;
	pixel_offset.y = (1 - 2 * (y + 0.5) / (double)HEIGHT) * fov_tan;
	pixel_offset.z = 0;
	return (pixel_offset);
}

/**
 * @brief Generates a primary ray from the camera through a specific pixel.
 * @param cam The active camera.
 * @param x The pixel's horizontal coordinate (from 0 to WIDTH-1).
 * @param y The pixel's vertical coordinate (from 0 to HEIGHT-1).
 * @return A t_ray struct containing the ray's origin and normalized direction.
 */
t_ray	generate_camera_ray(t_camera *cam, int x, int y)
{
	t_ray	ray;
	t_vec3	forward;
	t_vec3	right;
	t_vec3	up;
	t_vec3	pixel_offset;

	setup_camera_basis(cam, &forward, &right, &up);
	pixel_offset = calculate_pixel_on_plane(cam, x, y);
	ray.direction = vec3_add(vec3_mult(right, pixel_offset.x),
			vec3_mult(up, pixel_offset.y));
	ray.direction = vec3_add(ray.direction, forward);
	ray.origin = cam->position;
	ray.direction = vec3_normalize(ray.direction);
	return (ray);
}

/**
 * @brief Renders the entire scene by casting a ray for each pixel.
 * @param rt The main runtime structure containing the scene and MLX data.
 */
void	render_scene(t_rt *rt)
{
	int			x;
	int			y;
	t_camera	*active_cam;
	t_ray		ray;
	int			color;

	y = 0;
	active_cam = &rt->scene.cameras[rt->scene.active_camera_idx];
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ray = generate_camera_ray(active_cam, x, y);
			color = trace_ray(ray, &rt->scene, 0);
			my_mlx_pixel_put(&rt->data, x, y, color);
			x++;
		}
		y++;
	}
}

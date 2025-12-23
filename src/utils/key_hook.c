/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-lae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 12:34:32 by nvan-lae          #+#    #+#             */
/*   Updated: 2025/08/15 12:45:31 by nvan-lae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

static int	fov_change(int in_out, t_rt *rt)
{
	if (in_out == 1)
	{
		rt->scene.cameras[rt->scene.active_camera_idx].fov -= 5;
		if (rt->scene.cameras[rt->scene.active_camera_idx].fov < 1)
			rt->scene.cameras[rt->scene.active_camera_idx].fov = 1;
	}
	else if (in_out == -1)
	{
		rt->scene.cameras[rt->scene.active_camera_idx].fov += 5;
		if (rt->scene.cameras[rt->scene.active_camera_idx].fov > 179)
			rt->scene.cameras[rt->scene.active_camera_idx].fov = 179;
	}
	return (1);
}

int	key_hook(int keycode, t_rt *rt)
{
	int	re_render;

	re_render = 0;
	if (keycode == ESC_KEY)
		close_window(rt);
	else if (keycode == 65362)
		re_render = fov_change(1, rt);
	else if (keycode == 65364)
		re_render = fov_change(-1, rt);
	else if (keycode == 99)
	{
		rt->scene.active_camera_idx = (rt->scene.active_camera_idx + 1)
			% rt->scene.camera_count;
		re_render = 1;
	}
	if (re_render)
	{
		render_scene(rt);
		mlx_put_image_to_window(rt->data.mlx, rt->data.win, rt->data.img, 0, 0);
	}
	return (0);
}

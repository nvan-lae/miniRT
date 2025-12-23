/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-der <jvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 00:00:00 by jvan-der          #+#    #+#             */
/*   Updated: 2025/09/09 15:31:06 by nvan-lae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	init_mlx(t_rt *rt)
{
	rt->data.mlx = mlx_init();
	if (!rt->data.mlx)
		return (0);
	rt->scene.mlx = rt->data.mlx;
	rt->data.win = mlx_new_window(rt->data.mlx, WIDTH, HEIGHT, "miniRT");
	if (!rt->data.win)
		return (0);
	rt->data.img = mlx_new_image(rt->data.mlx, WIDTH, HEIGHT);
	if (!rt->data.img)
		return (0);
	rt->data.addr = mlx_get_data_addr(rt->data.img, &rt->data.bits_per_pixel,
			&rt->data.line_length, &rt->data.endian);
	return (1);
}

static void	setup_hooks(t_rt *rt)
{
	mlx_hook(rt->data.win, 17, 0, close_window, rt);
	mlx_key_hook(rt->data.win, key_hook, rt);
}

int	main(int argc, char **argv)
{
	t_rt	rt;

	if (argc != 2)
	{
		return (printf("Usage: %s <scene.rt>\n", argv[0]), 1);
	}
	if (ft_strlen(argv[1]) < 3
		|| ft_strncmp(argv[1] + ft_strlen(argv[1]) - 3, ".rt", 3) != 0)
		return (printf("Error: File must have .rt extension\n"), 1);
	check_scene_file(argv[1]);
	ft_memset(&rt.scene, 0, sizeof(t_scene));
	if (!init_mlx(&rt))
	{
		free_scene(&rt.scene);
		return (printf("Error: Failed to initialize MLX\n"), 1);
	}
	if (!parse_scene(argv[1], &rt.scene))
		return (printf("Error: Failed to parse scene file\n"), 1);
	rt.scene.active_camera_idx = 0;
	setup_hooks(&rt);
	render_scene(&rt);
	mlx_put_image_to_window(rt.data.mlx, rt.data.win, rt.data.img, 0, 0);
	mlx_loop(rt.data.mlx);
	get_next_line(-42);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-der <jvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 00:00:00 by jvan-der          #+#    #+#             */
/*   Updated: 2025/08/19 15:36:48 by nvan-lae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		dst = data->addr
			+ (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

int	close_window(t_rt *rt)
{
	free_scene(&rt->scene);
	mlx_destroy_image(rt->data.mlx, rt->data.img);
	mlx_destroy_window(rt->data.mlx, rt->data.win);
	mlx_destroy_display(rt->data.mlx);
	free(rt->data.mlx);
	exit(0);
}

int	create_rgb(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

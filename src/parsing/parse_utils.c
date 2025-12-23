/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-der <jvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 00:00:00 by jvan-der          #+#    #+#             */
/*   Updated: 2025/09/03 14:54:39 by nvan-lae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3	parse_vec3(char *str, int check_normalized)
{
	t_vec3	vec;
	char	**split;
	int		i;

	split = ft_split(str, ',');
	if (!split || !split[0] || !split[1] || !split[2])
		return ((t_vec3){0, 0, 0});
	vec.x = ft_atof(split[0]);
	vec.y = ft_atof(split[1]);
	vec.z = ft_atof(split[2]);
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	if (check_normalized)
	{
		if (fabs(vec3_length(vec) - 1.0) > 1e-6)
			vec = vec3_normalize(vec);
	}
	return (vec);
}

t_color	parse_color(char *str)
{
	t_color	color;
	char	**split;
	int		i;

	split = ft_split(str, ',');
	if (!split || !split[0] || !split[1] || !split[2])
		error_exit("Invalid color format");
	color.r = ft_atoi(split[0]);
	color.g = ft_atoi(split[1]);
	color.b = ft_atoi(split[2]);
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	if (color.r < 0 || color.r > 255
		|| color.g < 0 || color.g > 255 || color.b < 0 || color.b > 255)
		error_exit("Color value out of range (0-255)");
	return (color);
}

double	parse_double(char *str)
{
	return (ft_atof(str));
}

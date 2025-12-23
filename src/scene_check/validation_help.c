/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_help.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-lae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 13:13:50 by nvan-lae          #+#    #+#             */
/*   Updated: 2025/09/09 15:04:58 by nvan-lae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	validate_vector(char *s, int normalized)
{
	char	**parts;
	int		i;
	double	val;

	parts = ft_split(s, ',');
	if (arr_size(parts) != 3)
		return (free_array(parts), 0);
	i = -1;
	while (++i < 3)
	{
		if (!is_float(parts[i]))
			return (free_array(parts), 0);
		if (normalized)
		{
			val = ft_atof(parts[i]);
			if (val < -1.0 || val > 1.0)
				return (free_array(parts), 0);
		}
	}
	return (free_array(parts), 1);
}

int	validate_color(char *s)
{
	char	**parts;
	int		i;
	double	val;

	parts = ft_split(s, ',');
	if (arr_size(parts) != 3)
		return (free_array(parts), 0);
	i = -1;
	while (++i < 3)
	{
		if (!is_int(parts[i]))
			return (free_array(parts), 0);
		val = ft_atof(parts[i]);
		if (val < 0 || val > 255)
			return (free_array(parts), 0);
	}
	return (free_array(parts), 1);
}

int	validate_pos_float(char *s)
{
	double	val;

	if (!is_float(s))
		return (0);
	val = ft_atof(s);
	if (val <= 0)
		return (0);
	return (1);
}

int	validate_double_range(char *s, double min, double max)
{
	double	val;

	if (!is_float(s))
		return (0);
	val = ft_atof(s);
	if (val < min || val > max)
		return (0);
	return (1);
}

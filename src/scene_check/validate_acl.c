/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_acl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-lae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 12:54:07 by nvan-lae          #+#    #+#             */
/*   Updated: 2025/09/09 15:08:51 by nvan-lae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	validate_a(char **info)
{
	if (arr_size(info) != 3)
		return (error_msg("Wrong number of arguments for ambient light"));
	if (!validate_double_range(info[1], 0.0, 1.0))
		return (error_msg("Invalid ambient light ratio"));
	if (!validate_color(info[2]))
		return (error_msg("Invalid color for ambient light"));
	return (1);
}

int	validate_c(char **info)
{
	if (arr_size(info) != 4)
		return (error_msg("Wrong number of arguments for camera"));
	if (!validate_vector(info[1], 0))
		return (error_msg("Invalid vector for camera position"));
	if (!validate_vector(info[2], 1))
		return (error_msg("Invalid normal for camera"));
	if (!validate_double_range(info[3], 0, 180))
		return (error_msg("Invalid FOV for camera"));
	return (1);
}

int	validate_l(char **info)
{
	if (arr_size(info) != 4)
		return (error_msg("Wrong number of arguments for light"));
	if (!validate_vector(info[1], 0))
		return (error_msg("Invalid vector for light position"));
	if (!validate_double_range(info[2], 0.0, 1.0))
		return (error_msg("Invalid light brightness ratio"));
	if (!validate_color(info[3]))
		return (error_msg("Invalid color for light"));
	return (1);
}

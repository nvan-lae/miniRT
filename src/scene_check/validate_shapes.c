/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_shapes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-lae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 13:26:28 by nvan-lae          #+#    #+#             */
/*   Updated: 2025/09/09 15:09:17 by nvan-lae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	validate_sp(char **info)
{
	if (arr_size(info) < 4)
		return (error_msg("Wrong number of arguments for sphere"));
	if (!validate_vector(info[1], 0))
		return (error_msg("Invalid vector for sphere position"));
	if (!validate_pos_float(info[2]))
		return (error_msg("Invalid diameter for sphere"));
	if (!validate_color(info[3]))
		return (error_msg("Invalid color for sphere"));
	return (1);
}

int	validate_pl(char **info)
{
	if (arr_size(info) < 4)
		return (error_msg("Wrong number of arguments for plane"));
	if (!validate_vector(info[1], 0))
		return (error_msg("Invalid vector for plane position"));
	if (!validate_vector(info[2], 1))
		return (error_msg("Invalid normal for plane"));
	if (!validate_color(info[3]))
		return (error_msg("Invalid color for plane"));
	return (1);
}

int	validate_cy(char **info)
{
	if (arr_size(info) < 6)
		return (error_msg("Wrong number of arguments for cylinder"));
	if (!validate_vector(info[1], 0))
		return (error_msg("Invalid vector for cylinder position"));
	if (!validate_vector(info[2], 1))
		return (error_msg("Invalid normal for cylinder"));
	if (!validate_pos_float(info[3]))
		return (error_msg("Invalid diameter for cylinder"));
	if (!validate_pos_float(info[4]))
		return (error_msg("Invalid height for cylinder"));
	if (!validate_color(info[5]))
		return (error_msg("Invalid color for cylinder"));
	return (1);
}

int	validate_pa(char **info)
{
	if (arr_size(info) < 6)
		return (error_msg("Wrong number of arguments for paraboloid"));
	if (!validate_vector(info[1], 0))
		return (error_msg("Invalid vector for paraboloid position"));
	if (!validate_vector(info[2], 1))
		return (error_msg("Invalid normal for paraboloid"));
	if (!validate_pos_float(info[3]))
		return (error_msg("Invalid height for paraboloid"));
	if (!validate_pos_float(info[4]))
		return (error_msg("Invalid distance for paraboloid"));
	if (!validate_color(info[5]))
		return (error_msg("Invalid color for paraboloid"));
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-lae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 17:38:15 by nvan-lae          #+#    #+#             */
/*   Updated: 2025/08/07 17:39:32 by nvan-lae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_color	apply_ambient(t_color obj, t_ambient amb)
{
	t_color	result;

	result.r = (int)(obj.r * amb.ratio * (amb.color.r / 255.0));
	result.g = (int)(obj.g * amb.ratio * (amb.color.g / 255.0));
	result.b = (int)(obj.b * amb.ratio * (amb.color.b / 255.0));
	return (result);
}

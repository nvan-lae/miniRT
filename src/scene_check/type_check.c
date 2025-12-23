/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-lae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 13:11:47 by nvan-lae          #+#    #+#             */
/*   Updated: 2025/09/09 13:13:01 by nvan-lae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	is_int(char *s)
{
	int	i;

	i = 0;
	if (!s || !s[0])
		return (0);
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_float(char *s)
{
	int	i;
	int	has_dot;

	i = 0;
	has_dot = 0;
	if (!s || !s[0])
		return (0);
	if (s[i] == '-' || s[i] == '+')
		i++;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (s[i] == '.')
		{
			if (has_dot)
				return (0);
			has_dot = 1;
		}
		else if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

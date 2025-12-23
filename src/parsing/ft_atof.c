/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-lae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 14:53:18 by nvan-lae          #+#    #+#             */
/*   Updated: 2025/09/03 14:53:37 by nvan-lae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static const char	*skip_whitespace_and_sign(const char *str, int *sign)
{
	*sign = 1;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-')
	{
		*sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	return (str);
}

static const char	*parse_integer_part(const char *str, double *result)
{
	*result = 0.0;
	while (*str >= '0' && *str <= '9')
	{
		*result = *result * 10.0 + (*str - '0');
		str++;
	}
	return (str);
}

static double	parse_fractional_part(const char *str)
{
	double	fraction;
	double	power;

	fraction = 0.0;
	power = 1.0;
	if (*str == '.')
	{
		str++;
		while (*str >= '0' && *str <= '9')
		{
			fraction = fraction * 10.0 + (*str - '0');
			power *= 10.0;
			str++;
		}
	}
	if (power > 1.0)
		return (fraction / power);
	return (0.0);
}

double	ft_atof(const char *str)
{
	double	integer_part;
	double	fractional_part;
	int		sign;

	str = skip_whitespace_and_sign(str, &sign);
	str = parse_integer_part(str, &integer_part);
	fractional_part = parse_fractional_part(str);
	return (sign * (integer_part + fractional_part));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refraction.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-lae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:21:26 by nvan-lae          #+#    #+#             */
/*   Updated: 2025/09/03 12:27:33 by nvan-lae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
** Computes the refraction (transmitted) vector 
    for a ray passing through a surface.
** i   : incident vector (normalized)
** n   : surface normal (normalized)
** ior : index of refraction (e.g., 1.5 for glass)
** Returns the refracted direction as a t_vec3. 
    If total internal reflection occurs, returns (0,0,0).
*/

t_vec3	refract(t_vec3 i, t_vec3 n, double ior)
{
	double	cosi;
	double	eta;
	double	k;
	t_vec3	n_adjusted;

	n_adjusted = n;
	cosi = -fmax(-1.0, fmin(1.0, vec3_dot(i, n_adjusted)));
	eta = 1.0 / ior;
	if (cosi < 0)
	{
		cosi = -cosi;
		n_adjusted = vec3_mult(n_adjusted, -1);
		eta = ior;
	}
	k = 1 - eta * eta * (1 - cosi * cosi);
	if (k < 0)
		return ((t_vec3){0, 0, 0});
	return (vec3_add(vec3_mult(i, eta),
			vec3_mult(n_adjusted, (eta * cosi - sqrt(k)))));
}

/*
** Helper to compute Rs and Rp for Fresnel equations.
*/

static double	fresnel_rs(double etai, double etat, double cosi, double cost)
{
	double	rs;

	rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost));
	return (rs * rs);
}

static double	fresnel_rp(double etai, double etat, double cosi, double cost)
{
	double	rp;

	rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost));
	return (rp * rp);
}

/*
** Computes the Fresnel reflection coefficient for a given incident vector,
** surface normal, and index of refraction.
** Returns the reflection ratio (0.0 - 1.0).
*/

double	fresnel(t_vec3 i, t_vec3 n, double ior)
{
	double	cosi;
	double	etai;
	double	etat;
	double	sint;
	double	cost;

	cosi = fmax(-1.0, fmin(1.0, vec3_dot(i, n)));
	etai = 1.0;
	etat = ior;
	if (cosi > 0)
	{
		etai = ior;
		etat = 1.0;
	}
	sint = etai / etat * sqrt(fmax(0.0, 1 - cosi * cosi));
	if (sint >= 1)
		return (1.0);
	cost = sqrt(fmax(0.0, 1 - sint * sint));
	cosi = fabs(cosi);
	return ((fresnel_rs(etai, etat, cosi, cost)
			+ fresnel_rp(etai, etat, cosi, cost)) / 2.0);
}

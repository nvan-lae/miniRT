/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_material.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvan-lae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 15:33:36 by nvan-lae          #+#    #+#             */
/*   Updated: 2025/08/20 15:34:12 by nvan-lae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	set_material_properties(t_material *mat)
{
	if (mat->type == MAT_MIRROR)
		mat->reflection = 1.0;
	else
		mat->reflection = 0.1;
	if (mat->type == MAT_GLASS)
	{
		mat->refraction = 0.9;
		mat->ior = 1.5;
	}
	else
	{
		mat->refraction = 0.0;
		mat->ior = 1.0;
	}
}

static void	load_bump_map(t_material *mat, void *mlx, char *file)
{
	mat->bump_map.img = mlx_xpm_file_to_image(mlx, file,
			&mat->bump_map.width, &mat->bump_map.height);
	if (mat->bump_map.img)
	{
		mat->bump_map.addr = mlx_get_data_addr(mat->bump_map.img,
				&mat->bump_map.bits_per_pixel, &mat->bump_map.line_length,
				&mat->bump_map.endian);
	}
}

static void	parse_textures(char **parts, int i, t_material *mat, void *mlx)
{
	while (parts[i])
	{
		if (ft_strncmp(parts[i], "checker", 7) == 0)
		{
			mat->texture_type = TEX_CHECKER;
			if (parts[i + 1])
				mat->color2 = parse_color(parts[i + 1]);
		}
		if (ft_strncmp(parts[i], "bump", 4) == 0)
		{
			mat->texture_type = TEX_BUMPMAP;
			if (parts[i + 1])
				load_bump_map(mat, mlx, parts[i + 1]);
		}
		i++;
	}
}

t_material	parse_material(char **parts, int start_idx, void *mlx)
{
	t_material	mat;
	char		*type_str;

	mat.texture_type = TEX_NONE;
	mat.color2 = (t_color){0, 0, 0};
	mat.bump_map.img = NULL;
	if (!parts[start_idx])
	{
		mat.type = MAT_DIFFUSE;
		return (mat);
	}
	type_str = parts[start_idx];
	if (ft_strncmp(type_str, "mirror", 6) == 0)
		mat.type = MAT_MIRROR;
	else if (ft_strncmp(type_str, "glass", 5) == 0)
		mat.type = MAT_GLASS;
	else if (ft_strncmp(type_str, "shiny", 5) == 0)
		mat.type = MAT_SHINY;
	else
		mat.type = MAT_DIFFUSE;
	parse_textures(parts, start_idx, &mat, mlx);
	set_material_properties(&mat);
	return (mat);
}

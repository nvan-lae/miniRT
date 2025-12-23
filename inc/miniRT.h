/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-der <jvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 00:00:00 by jvan-der          #+#    #+#             */
/*   Updated: 2025/09/09 15:11:43 by nvan-lae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include "Libft/libft.h"
# include "minilibx/mlx.h"

# define WIDTH  1080
# define HEIGHT 720
# define ESC_KEY 65307

typedef enum e_objtype
{
	OBJ_NONE,
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER,
	OBJ_PARABOLOID
}	t_objtype;

/* Colors */
typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

/* 3D Vector */
typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

/* Ray structure */
typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
}	t_ray;

/* Camera */
typedef struct s_camera
{
	t_vec3	position;
	t_vec3	orientation;
	double	fov;
}	t_camera;

/* Ambient Light */
typedef struct s_ambient
{
	double	ratio;
	t_color	color;
}	t_ambient;

/* Light */
typedef struct s_light
{
	t_vec3	position;
	double	brightness;
	t_color	color;
}	t_light;

/* Texture types */
typedef enum e_texture_type
{
	TEX_NONE,
	TEX_CHECKER,
	TEX_BUMPMAP
}	t_texture_type;

/* Bump Textures*/
typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_texture;

/* Material types */
typedef enum e_mat_type
{
	MAT_DIFFUSE,
	MAT_MIRROR,
	MAT_GLASS,
	MAT_SHINY
}	t_mat_type;

/* Material properties */
typedef struct s_material
{
	t_mat_type		type;
	double			reflection;
	double			refraction;
	double			ior;
	t_texture_type	texture_type;
	t_color			color2;
	t_texture		bump_map;
}	t_material;

/* Sphere */
typedef struct s_sphere
{
	t_vec3		center;
	double		diameter;
	t_color		color;
	t_material	material;
}	t_sphere;

/* Plane */
typedef struct s_plane
{
	t_vec3		point;
	t_vec3		normal;
	t_color		color;
	t_material	material;
}	t_plane;

/* Cylinder */
typedef struct s_cylinder
{
	t_vec3		center;
	t_vec3		axis;
	double		diameter;
	double		height;
	t_color		color;
	t_material	material;
}	t_cylinder;

/* Paraboloid */
typedef struct s_paraboloid
{
	t_vec3		vertex;
	t_vec3		axis;
	double		k;
	double		height;
	t_color		color;
	t_material	material;
}	t_paraboloid;

/* Scene container */
typedef struct s_scene
{
	t_camera			*cameras;
	t_ambient			ambient;
	t_light				*lights;
	t_sphere			*spheres;
	t_plane				*planes;
	t_cylinder			*cylinders;
	t_paraboloid		*paraboloids;
	int					camera_count;
	int					active_camera_idx;
	int					light_count;
	int					sphere_count;
	int					plane_count;
	int					cylinder_count;
	int					paraboloid_count;
	void				*mlx;
}						t_scene;

/* MLX data */
typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

/* Main program structure */
typedef struct s_rt
{
	t_data	data;
	t_scene	scene;
}	t_rt;

/* Ray generation context */
typedef struct s_raygen_ctx
{
	double	aspect_ratio;
	double	fov_rad;
	double	pixel_ndc_x;
	double	pixel_ndc_y;
	double	pixel_screen_x;
	double	pixel_screen_y;
	double	pixel_camera_x;
	double	pixel_camera_y;
}	t_raygen_ctx;

/* Count Objects */
typedef struct s_count_objects
{
	int	sphere_count;
	int	plane_count;
	int	cylinder_count;
	int	paraboloid_count;
	int	light_count;
	int	camera_count;
	int	sphere_idx;
	int	plane_idx;
	int	cylinder_idx;
	int	paraboloid_idx;
	int	light_idx;
	int	camera_idx;
}	t_count_objects;

typedef struct s_hit
{
	t_objtype	type;
	void		*object;
	double		t;
}	t_hit;

typedef struct s_hit_info
{
	t_ray		ray;
	t_scene		*scene;
	int			depth;
	t_material	mat;
	t_vec3		hit_point;
	t_vec3		normal;
	t_color		base_color;
	t_color		final_color;
}				t_hit_info;

/* Function prototypes */

/* --- Parsing --- */
int			parse_scene(char *filename, t_scene *scene);
void		count_objects(const char *filename, t_count_objects *count);
void		malloc_objects(t_scene *scene, t_count_objects *count);
void		objects_zero(t_count_objects *count);

/* --- Object & Material Parsing --- */
int			parse_ambient(char *line, t_ambient *ambient);
int			parse_camera(char *line, t_camera *camera);
int			parse_light(char *line, t_light *light);
int			parse_sphere(char *line, t_sphere *sphere, void *mlx);
int			parse_plane(char *line, t_plane *plane, void *mlx);
int			parse_cylinder(char *line, t_cylinder *cylinder, void *mlx);
int			parse_paraboloid(char *line, t_paraboloid *para, void *mlx);
t_material	parse_material(char **parts, int start_idx, void *mlx);

/* --- Parsing Utilities --- */
t_vec3		parse_vec3(char *str, int check_normalized);
t_color		parse_color(char *str);
double		parse_double(char *str);
double		ft_atof(const char *str);

/* --- Vector Math --- */
t_vec3		vec3_add(t_vec3 a, t_vec3 b);
t_vec3		vec3_sub(t_vec3 a, t_vec3 b);
t_vec3		vec3_mult(t_vec3 v, double scalar);
double		vec3_dot(t_vec3 a, t_vec3 b);
t_vec3		vec3_cross(t_vec3 a, t_vec3 b);
double		vec3_length(t_vec3 v);
t_vec3		vec3_normalize(t_vec3 v);
t_vec3		get_hit_point(t_ray ray, double t);
t_color		calculate_lighting(t_ray ray, t_scene *scene, t_hit closest);
t_color		calculate_material_effects(t_ray r, t_scene *s, t_hit c, int d);
t_material	get_material(t_hit *closest);
t_color		get_textured_color(t_hit *closest, t_vec3 hit_point);
t_vec3		get_normal(t_hit hit, t_ray ray);

/* --- Ray Tracing & Intersections --- */
int			trace_ray(t_ray ray, t_scene *scene, int depth);
int			ray_sphere_intersection(t_ray ray, t_sphere sphere, double *t);
int			ray_plane_intersection(t_ray ray, t_plane plane, double *t);
int			ray_cylinder_intersection(t_ray ray, t_cylinder cyl, double *t);
int			ray_paraboloid_intersection(t_ray ray, t_paraboloid pa, double *t);

/* --- Rendering & Window --- */
void		render_scene(t_rt *rt);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
int			close_window(t_rt *rt);
int			key_hook(int keycode, t_rt *rt);

/* --- Color & Lighting --- */
int			create_rgb(int r, int g, int b);
t_color		apply_ambient(t_color obj, t_ambient amb);
int			shadow_hits_paraboloid(t_ray s_ray, t_scene *s, double l_dist);
int			shadow_hits_cylinder(t_ray s_ray, t_scene *s, double l_dist);
int			shadow_hits_plane(t_ray s_ray, t_scene *s, double l_dist);
int			shadow_hits_sphere(t_ray s_ray, t_scene *s, double l_dist);

/* --- UV Mapping --- */
void		get_sphere_uv(t_vec3 p, double *u, double *v);
void		get_plane_uv(t_vec3 p, t_vec3 normal, double *u, double *v);
void		get_object_uv(t_hit hit, t_vec3 hit_point, double *u, double *v);

/* --- Memory & Error Management --- */
void		free_scene(t_scene *scene);
void		error_exit(char *message);
int			error_msg(char *message);

/* --- Bump Mapping --- */
t_vec3		get_bump_normal(t_hit h, t_vec3 hp, t_vec3 n, t_material mat);

/* --- Refraction --- */
t_vec3		refract(t_vec3 I, t_vec3 N, double ior);
double		fresnel(t_vec3 I, t_vec3 N, double ior);

/* --- Spheres --- */
t_vec3		get_normal_sphere(t_hit hit, t_ray ray);
void		find_closest_object_sphere(t_ray r, t_scene *s, t_hit *c);

/* --- Planes --- */
t_vec3		get_normal_plane(t_hit hit);
void		find_closest_object_plane(t_ray r, t_scene *s, t_hit *c);

/* --- Cylinder --- */
t_vec3		get_normal_cylinder(t_hit hit, t_ray ray);
void		find_closest_object_cylinder(t_ray r, t_scene *s, t_hit *c);

/* --- Paraboloid --- */
t_vec3		get_normal_paraboloid(t_hit hit, t_ray ray);
void		find_closest_object_paraboloid(t_ray r, t_scene *s, t_hit *c);

/* --- Scene Checking --- */
void		check_scene_file(const char *filename);
int			validate_a(char **info);
int			validate_c(char **info);
int			validate_l(char **info);
int			validate_sp(char **info);
int			validate_pl(char **info);
int			validate_cy(char **info);
int			validate_pa(char **info);
void		free_array(char **arr);
int			validate_vector(char *s, int normalized);
int			validate_color(char *s);
int			validate_pos_float(char *s);
int			validate_double_range(char *s, double min, double max);
int			arr_size(char **arr);
int			is_int(char *s);
int			is_float(char *s);

#endif

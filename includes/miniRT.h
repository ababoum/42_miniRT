/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 19:35:10 by mababou           #+#    #+#             */
/*   Updated: 2022/04/28 15:25:05 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "types.h"
# include "../minilibx-linux/mlx.h"
# include "ft3d.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>

// mlx tools
void		mlx_start(t_data *data);
void		img_init(t_data *data);
void		data_init(t_data *data, const char *path);
void		mlx_events(t_data *data);
int			add_color(int rgb1, int rgb2);

// colors
int			check_int_color(int rgb[3]);
int			rgb_to_int(int rgb[3]);

// memory & frees
void		*malloc_log(t_data *data, int size);
void		*img_log(t_data *data, int width, int height);
t_data		*get_data(int code, t_data *input);
void		clear_exit(t_data *data, int exit_code);
void		exit_message(t_data *data, char *message, int exit_code);

// get next line
int			find_char(char *str, char c);
int			ft_strlen(const char *str);
void		ft_memset(void *ptr, int val, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
char		*get_next_line(int fd);

// strings & numbers
int			ft_strcmp(const char *s1, const char *s2);
int			is_char(char c, const char *set);
char		**ft_split(t_data *data, char *s, const char *set);
int			tab_len(char **tab);
int			ft_atoi(const char *str);
float		ft_atof(char *str);

// strings display
void		ft_putstr_fd(char *str, int fd);

// objects
t_obj		*new_obj(t_data *data, void *ptr, int type);
void		obj_add_back(t_obj **alst, t_obj *new);
t_sphere	*new_sphere(t_data *data);
t_plan		*new_plan(t_data *data);
t_cylinder	*new_cylinder(t_data *data);

// parsing
void		parse_input(t_data *data, const char *path);
int			verify_file(t_data *data, const char *path);
void		check_line_args(t_data *data, char *type, int argc);
void		check_scene_setting(t_data *data, int setting_type);
void		check_arg(t_data *data, char **arg, int argc, char *msg_if_fail);

// populate data
void		populate_amb(t_data *data, char *line);
void		populate_light(t_data *data, char *line);
void		populate_cam(t_data *data, char *line);
void		populate_plan(t_data *data, char *line);
void		populate_sphere(t_data *data, char *line);
void		populate_cyl(t_data *data, char *line);

// Screen drawing
void		pixel_put(t_data *data, int x, int y, int color);

// 3D geometry
t_3D_point	*dot_3d(float x, float y, float z);
void		set_3d_point(t_3D_point *pt, float x, float y, float z);
int			check_dir_vector(t_vec *vector);
int			check_dir_vector_p(t_3D_point *point);
void		normalize(t_3D_point *ray);
void		ray_mult_mat(t_ray *ray, t_m4 mat);

// vectors maths
t_vec		*vector(t_3D_point *p0, t_3D_point *p1);
t_vec		*vector_f(float x, float y, float z);
void		set_vector(t_vec *v, float x, float y, float z);
float		scalar(t_vec *v1, t_vec *v2);
float		norm(t_3D_point *pt);
float		norm_v(t_vec *v);
void		normalize(t_3D_point *pt);
void		normalize_v(t_vec *v);

// intersections
	// sphere
int			intersection_pt_sp(t_ray *ray, t_sphere *sp, t_3D_point *pt);
void		projection_pt_droite(t_ray *ray, t_3D_point *pt, t_3D_point *res);
	// plan


// maths
float		distance_2d(t_2D_point *A, t_2D_point *B);
float		distance_3d(t_3D_point *A, t_3D_point *B);
float		ffabs(float f);
int			rgb_factor(int rgb, float factor);

// vision
float		max_vision_axis(float fov);

// tests
void		draw_circle(t_data *data, t_2D_point *center, float radius);
void		draw_sp(t_data *data);

// RGB
int			rgb_ambiant(int rgb, int *lrgb, float grad);
int			arr_toRGB(int *rgb);

#endif
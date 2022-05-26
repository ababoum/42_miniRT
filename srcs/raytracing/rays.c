/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 16:18:57 by mababou           #+#    #+#             */
/*   Updated: 2022/05/26 20:52:29 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	prepare_initial_ray(t_ray *ray, t_data *data, int pos, t_m4 mat)
{
	float	ratio;
	float	x_ecran;
	float	y_ecran;

	ratio = WIN_HEIGHT * 1.0f / WIN_WIDTH;
	x_ecran = (pos % WIN_WIDTH * 1.0f) / WIN_WIDTH * 2.0f - 1;
	y_ecran = ((pos / WIN_WIDTH * 1.0f) / WIN_HEIGHT * 2.0f - 1) * ratio;
	set_point(&ray->origin, 0, 0, 0);
	set_vector(&ray->dir, \
		x_ecran * 1.0f, \
		1 / tanf(0.5f * data->cam->fov * 2 * M_PI / 180.0), \
		y_ecran * 1.0f);
	ray_mult_mat(ray, mat);
	normalize_v(&ray->dir);
}

void	set_direction_ray_pt(t_ray *ray, float x, float y, float z)
{
	set_vector(&ray->dir, x - ray->origin.x, \
				y - ray->origin.y, \
				z - ray->origin.z);
}

int	compute_pixel_color(int pixel, t_data *data, t_m4 mat)
{
	int		color;
	float	distance;
	t_obj	*obj;
	t_ray	ray;

	color = 0;
	obj = data->obj_lst;
	distance = -1;
	while (obj)
	{
		prepare_initial_ray(&ray, data, pixel, mat);
		if (obj->type == SPHERE)
			get_color_sphere(&ray, (t_sphere *)(obj->ptr), &color, &distance);
		else if (obj->type == PLAN)
			get_color_plan(&ray, (t_plan *)(obj->ptr), &color, &distance);
		else if (obj->type == CYLINDER)
			get_color_cyl(&ray, (t_cyl *)(obj->ptr), &color, &distance);
		else if (obj->type == CONE)
			get_color_cone(&ray, (t_cone *)(obj->ptr), &color, &distance);
		obj = obj->next;
	}
	return (color);
}

int	calc_spot(t_ray *norm, t_ray *ray, t_light *light, int *rgb)
{
	t_vec	vec;
	float	f;
	int		color;
	t_data	*data;

	data = get_data(0, 0);
	set_vector(&vec, light->src.x - norm->origin.x, \
		light->src.y - norm->origin.y, \
		light->src.z - norm->origin.z);
	color = 0;
	if (!object_between(&light->src, &norm->origin, data))
	{
		normalize_v(&vec);
		f = scalar(vec, norm->dir);
//		if (f < 0)
//			f = -f;
		if (f >= 0)
		{
			color = rgb_ambiant(arr_to_rgb(rgb), light->rgb, f * light->pow);
			color = add_color(color, calc_phong(norm, ray, light));
		}
	}
	if (light->next)
		color = add_color(color, calc_spot(norm, ray, light->next, rgb));
	return (color);
}

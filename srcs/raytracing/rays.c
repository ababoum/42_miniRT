/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 16:18:57 by mababou           #+#    #+#             */
/*   Updated: 2022/05/04 11:44:31 by mababou          ###   ########.fr       */
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

	// TODO check FOV

	set_3d_point(&ray->origin, 0, 0, 0);
	set_vector(&ray->dir, \
		x_ecran * 1.0f, \
		1 / tanf(0.5f * data->cam->fov * 2 * M_PI / 180.0), \
		y_ecran * 1.0f);
	ray_mult_mat(ray, mat);
	normalize_v(&ray->dir);
}

int	compute_pixel_color(t_ray *ray, t_data *data)
{
	int		color;
	t_obj	*obj;

	color = 0;
	obj = data->obj_lst;
	while (obj)
	{
		if (obj->type == SPHERE)
			analyze_ray_for_sphere(ray, (t_sphere *)(obj->ptr), &color);
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
	set_vector(&vec, light->src->x - norm->origin.x, \
		light->src->y - norm->origin.y, \
		light->src->z - norm->origin.z);
	if (object_between(light->src, &norm->origin, ray, data))
		return (0);
	normalize_v(&vec);
	f = scalar(&vec, &norm->dir);
	if (f < 0)
		f = 0;
	color = (rgb_ambiant(arr_toRGB(rgb), light->rgb, f * light->pow));
	//specular
	if (f >= 0.98f)
	{
		f = (f - 0.98f) / 0.02f;
		color = add_color(color, \
			rgb_ambiant(arr_toRGB(light->rgb), light->rgb, f * light->pow));
	}
	return (color);
}

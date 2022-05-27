/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_pl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 20:58:43 by mababou           #+#    #+#             */
/*   Updated: 2022/05/27 18:26:20 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static void
	plan_texture(t_plan *pl, t_vec *norm_dir, t_impact *impact)
{
	int		x_y[2];
	float	ax;
	float	ay;
	t_m4	mat;

	if (pl->texture)
	{
		x_y[0] = (int)(impact->tx * 40);
		x_y[1] = (int)(impact->ty * 40);
		get_h(&x_y[0], &x_y[1], pl->texture);
		ax = atanf(x_y[0]) / 8;
		ay = atanf(x_y[1]) / 8;
		set_identity(&mat);
		rotate_x_mat(&mat, ax);
		rotate_z_mat(&mat, ay);
		vec_mult_mat(norm_dir, mat);
	}
}

void	get_color_plan(t_ray *ray, t_plan *pl, int *color, float *dist)
{
	t_data		*data;
	t_impact	impact;
	t_ray		norm;

	set_point(&(impact.pt), 0, 0, 0);
	data = get_data(0, 0);
	if (intersection_impact_pl(ray, pl, &impact))
	{
		if (distance_3d(data->cam->pov, impact.pt) > *dist && *dist >= 0)
			return ;
		*dist = distance_3d(data->cam->pov, impact.pt);
		*color = rgb_ambiant(arr_to_rgb(impact.rgb), \
			data->amb->rgb, data->amb->grad);
		set_point(&norm.origin, impact.pt.x, impact.pt.y, impact.pt.z);
		set_vector(&norm.dir, pl->normal.x,
			pl->normal.y,
			pl->normal.z);
		plan_texture(pl, &norm.dir, &impact);
		normalize_v(&norm.dir);
		*color = add_color(*color, \
					calc_spot(&norm, ray, data->light_lst, impact.rgb));
	}
}

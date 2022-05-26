/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_pl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 20:58:43 by mababou           #+#    #+#             */
/*   Updated: 2022/05/26 21:06:12 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void get_color_plan(t_ray *ray, t_plan *pl, int *color, float *distance)
{
	t_data		*data;
	t_impact	impact;
	t_ray		norm;
	float		dist;
	int			x;
	int			y;

	set_point(&(impact.pt), 0, 0, 0);
	data = get_data(0, 0);
	if (intersection_impact_pl(ray, pl, &impact))
	{
		dist = distance_3d(data->cam->pov, impact.pt);
		if (dist > *distance && *distance >= 0)
			return ;
		*distance = dist;
		// Ambiant light
		*color = rgb_ambiant(arr_to_rgb(impact.rgb), \
			data->amb->rgb, data->amb->grad);
		set_point(&norm.origin, impact.pt.x, impact.pt.y, impact.pt.z);
		set_vector(&norm.dir, pl->normal.x,
			pl->normal.y,
			pl->normal.z);

		if (pl->texture)
		{
			x = (int) (impact.tx * 40);
			y = (int) (impact.ty * 40);
			get_h(&x, &y, pl->texture);
			float ax = atanf(x) / 8;
			float ay = atanf(y) / 8;
			t_m4 mat;
			set_identity(&mat);
			rotate_x_mat(&mat, ax);
			rotate_z_mat(&mat, ay);
			vec_mult_mat(&norm.dir, mat);
		}

		normalize_v(&norm.dir);
		*color = add_color(*color, \
					calc_spot(&norm, ray, data->light_lst, impact.rgb));
	}
}

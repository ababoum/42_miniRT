/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_cn.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 21:07:29 by mababou           #+#    #+#             */
/*   Updated: 2022/05/26 21:15:31 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	get_color_cone(t_ray *ray, t_cone *cone, int *color, float *distance)
{
	t_data *data;
	t_impact impact;
	t_ray norm;
	t_vec tmp1;
	t_vec tmp2;

	float v;
	float dist;
	int ret;
	int x;
	int y;

	data = get_data(0, 0);
	ret = intersection_impact_cone(ray, cone, &impact);
	if (ret)
	{
		dist = distance_3d(data->cam->pov, impact.pt);
		if (dist > *distance && *distance >= 0)
			return;
		*distance = dist;
		*color = rgb_ambiant(arr_to_rgb(impact.rgb), \
            data->amb->rgb, data->amb->grad);

		set_point(&norm.origin, impact.pt.x, impact.pt.y, impact.pt.z);
		v = distance_3d(impact.pt, cone->center);

		set_vector(&tmp1, impact.pt.x - cone->center.x, \
            impact.pt.y - cone->center.y, \
            impact.pt.z - cone->center.z);
		set_vector(&tmp2, -v * cone->dir.x, \
            -v * cone->dir.y, \
            -v * cone->dir.z);
		if (vec_dot(tmp1, tmp2) < 0)
			v *= -1;

		set_vector(&norm.dir, cone->center.x - v * cone->dir.x, \
            cone->center.y - v * cone->dir.y, \
            cone->center.z - v * cone->dir.z);

		if (cone->texture)
		{
			x = (int) (impact.tx);
			y = (int) (impact.ty * 20);
			get_h(&x, &y, cone->texture);
			float ax = atanf(x) / 40;
			float ay = atanf(y) / 40;
			t_m4 mat;
			set_identity(&mat);
			rotate_x_mat(&mat, ax);
			rotate_z_mat(&mat, ay);
			vec_mult_mat(&norm.dir, mat);
		}

		norm.dir.x = impact.pt.x - norm.dir.x;
		norm.dir.y = impact.pt.y - norm.dir.y;
		norm.dir.z = impact.pt.z - norm.dir.z;

		normalize_v(&norm.dir);
		*color = add_color(*color, \
				calc_spot(&norm, ray, data->light_lst, impact.rgb));
		// spot ?
	}
}

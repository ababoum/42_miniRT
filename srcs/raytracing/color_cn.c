/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_cn.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 21:07:29 by mababou           #+#    #+#             */
/*   Updated: 2022/05/27 17:35:18 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static void
	cone_texture(t_cone *cone, t_vec *norm_dir, t_impact *impact)
{
	float	ax;
	float	ay;
	t_m4	mat;
	int		x_y[2];

	if (cone->texture)
	{
		x_y[0] = (int)(impact->tx);
		x_y[1] = (int)(impact->ty * 20);
		get_h(&x_y[0], &x_y[1], cone->texture);
		ax = atanf(x_y[0]) / 40;
		ay = atanf(x_y[1]) / 40;
		set_identity(&mat);
		rotate_x_mat(&mat, ax);
		rotate_z_mat(&mat, ay);
		vec_mult_mat(norm_dir, mat);
	}
}

static void	process_cone_normal(t_ray *norm, t_impact *impact, t_cone *cone)
{
	float	v;
	t_vec	tmp1;
	t_vec	tmp2;

	set_point(&norm->origin, impact->pt.x, impact->pt.y, impact->pt.z);
	v = distance_3d(impact->pt, cone->center);
	set_vector(&tmp1, impact->pt.x - cone->center.x, \
		impact->pt.y - cone->center.y, \
		impact->pt.z - cone->center.z);
	set_vector(&tmp2, -v * cone->dir.x, \
		-v * cone->dir.y, \
		-v * cone->dir.z);
	if (vec_dot(tmp1, tmp2) < 0)
		v *= -1;
	set_vector(&norm->dir, cone->center.x - v * cone->dir.x, \
		cone->center.y - v * cone->dir.y, \
		cone->center.z - v * cone->dir.z);
}

void	get_color_cone(t_ray *ray, t_cone *cone, int *color, float *dist)
{
	t_data		*data;
	t_impact	impact;
	t_ray		norm;
	int			ret;

	data = get_data(0, 0);
	ret = intersection_impact_cone(ray, cone, &impact);
	if (ret)
	{
		if (distance_3d(data->cam->pov, impact.pt) > *dist && *dist >= 0)
			return ;
		*dist = distance_3d(data->cam->pov, impact.pt);
		*color = rgb_ambiant(arr_to_rgb(impact.rgb), \
			data->amb->rgb, data->amb->grad);
		process_cone_normal(&norm, &impact, cone);
		cone_texture(cone, &norm.dir, &impact);
		norm.dir.x = impact.pt.x - norm.dir.x;
		norm.dir.y = impact.pt.y - norm.dir.y;
		norm.dir.z = impact.pt.z - norm.dir.z;
		normalize_v(&norm.dir);
		*color = add_color(*color, \
				calc_spot(&norm, ray, data->light_lst, impact.rgb));
	}
}

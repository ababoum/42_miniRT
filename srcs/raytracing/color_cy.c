/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_cy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 21:06:35 by mababou           #+#    #+#             */
/*   Updated: 2022/05/27 18:28:39 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

// parameters to modify in the texture
static void
	cyl_texture(t_cyl *cy, t_vec *norm_dir, t_impact *impact)
{
	float	ax;
	float	ay;
	t_m4	mat;
	int		x_y[2];

	if (cy->texture)
	{
		x_y[0] = (int)(impact->tx); // to set
		x_y[1] = (int)(impact->ty * 20); // to set
		get_h(&x_y[0], &x_y[1], cy->texture);
		ax = atanf(x_y[0]) / 40; // to set
		ay = atanf(x_y[1]) / 40; // to set
		set_identity(&mat);
		rotate_x_mat(&mat, ax);
		rotate_z_mat(&mat, ay);
		vec_mult_mat(norm_dir, mat);
	}
}

static void
	process_cyl_normal(t_ray *norm, t_impact *impact, t_cyl *cy, int *ret)
{
	float	v;

	set_point(&norm->origin, impact->pt.x, impact->pt.y, impact->pt.z);
	set_vector(&norm->dir, impact->pt.x - cy->point.x, \
			impact->pt.y - cy->point.y, \
			impact->pt.z - cy->point.z);
	if (*ret == 2)
	{
		v = vec_dot(cy->dir, norm->dir);
		if (v > 0)
			set_vector(&norm->dir, cy->dir.x, cy->dir.y, cy->dir.z);
		else
			set_vector(&norm->dir, -cy->dir.x, -cy->dir.y, -cy->dir.z);
	}
	else
	{
		v = vec_dot(cy->dir, norm->dir);
		norm->dir.x -= v * cy->dir.x;
		norm->dir.y -= v * cy->dir.y;
		norm->dir.z -= v * cy->dir.z;
	}
}

void	get_color_cyl(t_ray *ray, t_cyl *cy, int *color, float *dist)
{
	t_data		*data;
	t_impact	impact;
	t_ray		norm;
	int			ret;

	data = get_data(0, 0);
	ret = intersection_impact_cy(ray, cy, &impact);
	if (ret)
	{
		if (distance_3d(data->cam->pov, impact.pt) > *dist && *dist >= 0)
			return ;
		*dist = distance_3d(data->cam->pov, impact.pt);
		*color = rgb_ambiant(arr_to_rgb(impact.rgb), \
			data->amb->rgb, data->amb->grad);
		process_cyl_normal(&norm, &impact, cy, &ret);
		cyl_texture(cy, &norm.dir, &impact);
		normalize_v(&norm.dir);
		*color = add_color(*color, \
					calc_spot(&norm, ray, data->light_lst, impact.rgb));

	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_pl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 12:02:08 by mababou           #+#    #+#             */
/*   Updated: 2022/05/05 11:48:21 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

// warning: the ray needs to be normalized
int intersection_impact_pl(t_ray *ray, t_plan *pl, t_impact *impact)
{
	float disc[2];
	t_m4 mat;
	float rot_angles[2];
	t_3D_point p;

	disc[0] = scalar(pl->normal, vector(pl->point, ray->origin));
	disc[1] = scalar(pl->normal, ray->dir);
	if (disc[1] >= 0 || disc[0] == 0)
		return (0);
	set_point(&(impact->pt),
			  ray->origin.x + (disc[0] / disc[1]) * ray->dir.x,
			  ray->origin.y + (disc[0] / disc[1]) * ray->dir.y,
			  ray->origin.z + (disc[0] / disc[1]) * ray->dir.z);


	set_identity(&mat);
	rot_angles[0] = get_angle(pl->normal.x, pl->normal.y) + M_PI_2;
	rot_angles[1] = get_angle(sqrtf(pl->normal.x * pl->normal.x + \
                        pl->normal.y * pl->normal.y), \
                        pl->normal.z);
//	rotate_z_mat(&mat, M_PI);
	rotate_x_mat(&mat, rot_angles[1]);
	rotate_z_mat(&mat, -rot_angles[0]);

	p.x = impact->pt.x;
	p.y = impact->pt.y;
	p.z = impact->pt.z;

	pt3d_mult_mat(&p, mat);
	if (p.x < 0)
		p.x = -p.x + DAMIER_FACTOR/40.0;
	if (p.z < 0)
		p.z = -p.z + DAMIER_FACTOR/40.0;
	if ((fmod(p.x * DAMIER_FACTOR / 20, 1) > 0.5) ^ (fmod(p.z * DAMIER_FACTOR / 20, 1) > 0.5))
		impact->rgb = pl->rgb;
	else
		impact->rgb = pl->rgb2;
	return (1);
}

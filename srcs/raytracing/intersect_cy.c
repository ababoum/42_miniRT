/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:23:31 by mababou           #+#    #+#             */
/*   Updated: 2022/06/20 18:03:33 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static void	prepare_ray_for_cy(t_ray *ray, t_cyl *cy)
{
	t_m4	mat;
	float	rot_angles[2];

	set_identity(&mat);
	rot_angles[0] = get_angle(cy->dir.x, cy->dir.y) + M_PI_2;
	rot_angles[1] = get_angle(sqrtf(cy->dir.x * cy->dir.x + \
		cy->dir.y * cy->dir.y), \
		cy->dir.z);
	rotate_x_mat(&mat, rot_angles[1]);
	rotate_z_mat(&mat, -rot_angles[0]);
	translate_mat(&mat, -cy->point.x, -cy->point.y, -cy->point.z);
	ray_mult_mat(ray, mat);
}

void	reverse_op(t_cyl *cy, t_3D_point *pt)
{
	t_m4	mat;
	float	rot_angles[2];

	set_identity(&mat);
	rot_angles[0] = get_angle(cy->dir.x, cy->dir.y) + M_PI_2;
	rot_angles[1] = get_angle(sqrtf(cy->dir.x * cy->dir.x + \
		cy->dir.y * cy->dir.y), \
		cy->dir.z);
	translate_mat(&mat, cy->point.x, cy->point.y, cy->point.z);
	rotate_z_mat(&mat, rot_angles[0]);
	rotate_x_mat(&mat, -rot_angles[1]);
	pt3d_mult_mat(pt, mat);
}

// cy_switch val tests if the ray intersects the cylinder caps.
// if it does, it updates the parameter value (t_) that satisfies the 
// intersection (the closest one if 2 solutions are found)
static int	intersection_cy_caps(t_ray *ray, t_cyl *cy, t_impact *impact)
{
	float	t_;

	if (!cy_switch_val(ray, cy, &t_))
		return (0);
	set_point(&(impact->pt), ray->origin.x + t_ * ray->dir.x, \
		ray->origin.y + t_ * ray->dir.y, ray->origin.z + t_ * ray->dir.z);
	impact->tx = impact->pt.z / cy->radius * TEXTURE_SIZE / 2
		+ TEXTURE_SIZE / 2;
	impact->ty = -impact->pt.x / cy->radius * TEXTURE_SIZE / 2
		+ TEXTURE_SIZE / 2;
	if ((fmod(get_angle(impact->pt.x, impact->pt.z) * DAMIER_FACTOR / M_PI,
				1.0) > 0.5) ^ \
		(fmod(sqrtf(impact->pt.x * impact->pt.x + impact->pt.z * impact->pt.z)
				/ 2 * DAMIER_FACTOR / M_PI, 1.0) > 0.5))
		impact->rgb = cy->rgb;
	else
		impact->rgb = cy->rgb2;
	reverse_op(cy, &(impact->pt));
	return (2);
}

int	dbl_intersection_pt_cy(t_ray *ray, t_cyl *cy, t_impact *im, \
	t_eq_param eq_sys)
{
	float	t[2];
	float	t_;

	t[0] = (-eq_sys.b + sqrtf(eq_sys.delta)) / (2 * eq_sys.a);
	t[1] = (-eq_sys.b - sqrtf(eq_sys.delta)) / (2 * eq_sys.a);
	if (t[0] < 0 && t[1] < 0)
		return (0);
	else if ((t[0] < -EPSILON && t[1] >= EPSILON)
		|| (t[1] < -EPSILON && t[0] >= EPSILON))
		t_ = max(t[0], t[1]);
	else
		t_ = min(t[0], t[1]);
	if (!is_between(ray->origin.y + ray->dir.y * t_, \
				-cy->height / 2, cy->height / 2))
		return (intersection_cy_caps(ray, cy, im));
	set_point(&(im->pt), ray->origin.x + t_ * ray->dir.x, \
			ray->origin.y + t_ * ray->dir.y, ray->origin.z + t_ * ray->dir.z);
	im->tx = im->pt.y / cy->height * TEXTURE_SIZE;
	im->ty = get_angle(im->pt.x, im->pt.z) * TEXTURE_SIZE / M_PI;
	im->rgb = cy->rgb2;
	if ((fmod(get_angle(im->pt.x, im->pt.z) * DAMIER_FACTOR / M_PI, 1) > .5)
		^ (fmod((cy->height + im->pt.y) / 2 * DAMIER_FACTOR / M_PI, 1) > .5))
		im->rgb = cy->rgb;
	reverse_op(cy, &(im->pt));
	return (1);
}

int	intersection_impact_cy(t_ray *ray, t_cyl *cy, t_impact *impact)
{
	t_eq_param	eq_sys;

	prepare_ray_for_cy(ray, cy);
	discriminant_cy_2(ray, cy, &eq_sys);
	if (eq_sys.delta < 0)
		return (intersection_cy_caps(ray, cy, impact));
	else
		return (dbl_intersection_pt_cy(ray, cy, impact, eq_sys));
}

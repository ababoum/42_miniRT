/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 16:18:57 by mababou           #+#    #+#             */
/*   Updated: 2022/04/29 16:48:41 by mababou          ###   ########.fr       */
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

	set_3d_point(ray->origin, 0, 0, 0);
	set_vector(ray->dir, \
		x_ecran * 1.0f, \
		1 / tanf(0.5f * data->cam->fov * 2 * M_PI / 180.0), \
		y_ecran * 1.0f);
	ray_mult_mat(ray, mat);
	normalize_v(ray->dir);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:56:12 by mababou           #+#    #+#             */
/*   Updated: 2022/06/06 16:02:38 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static void	prepare_vec_l(t_vec *vec_l, t_ray *norm, t_light *light)
{
	set_vector(vec_l, light->src.x - norm->origin.x, \
		light->src.y - norm->origin.y, \
		light->src.z - norm->origin.z);
}

static void	prepare_vec(t_vec *vec, t_ray *norm, t_ray *ray)
{
	float	d;

	d = -vec_dot(norm->dir, ray->dir);
	set_vector(vec, \
				ray->dir.x + 2 * d * norm->dir.x, \
				ray->dir.y + 2 * d * norm->dir.y, \
				ray->dir.z + 2 * d * norm->dir.z \
	);
	normalize_v(vec);
}

int	calc_phong(t_ray *norm, t_ray *ray, t_light *light)
{
	t_vec	vec;
	t_vec	vec_l;
	float	d;
	float	n;
	t_data	*data;

	data = get_data(0, 0);
	if (!data->bonus)
		return (0);
	prepare_vec_l(&vec_l, norm, light);
	n = norm_v(&vec_l);
	normalize_v(&vec_l);
	prepare_vec(&vec, norm, ray);
	d = acosf(vec_dot(vec, vec_l));
	if (n > 0.1)
		d *= n * n;
	if (d < PHONG_SIZE)
	{
		d /= PHONG_SIZE;
		return (add_color(0, rgb_factor(rgb_to_int(light->rgb), \
											light->pow * (1 - powf(d, 1)))));
	}
	else
		return (0);
}

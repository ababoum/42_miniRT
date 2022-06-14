/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cy2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 12:12:49 by mababou           #+#    #+#             */
/*   Updated: 2022/05/05 14:42:44 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static int	is_cap_met(t_ray *ray, t_cyl *cy, float t, float *t_)
{
	if (powf(ray->origin.x + t * ray->dir.x, 2) + \
		powf(ray->origin.z + t * ray->dir.z, 2) <= powf(cy->radius, 2))
	{
		*t_ = t;
		return (1);
	}
	else
		return (0);
}

static void	init_cap_values(t_ray *ray, t_cyl *cy, float *t_top, float *t_bot)
{
	*t_top = ((cy->height / 2) - ray->origin.y) / ray->dir.y;
	*t_bot = ((-cy->height / 2) - ray->origin.y) / ray->dir.y;
}

int	cy_switch_val(t_ray *ray, t_cyl *cy, float *t_)
{
	float (t_top), t_bot;
	init_cap_values(ray, cy, &t_top, &t_bot);
	if (is_cap_met(ray, cy, t_bot, t_) && is_cap_met(ray, cy, t_top, t_))
	{
		if (t_top * t_bot < 0)
			*t_ = max(t_top, t_bot);
		else if (t_top < 0)
			return (0);
		else
			*t_ = min(t_top, t_bot);
	}
	else if (is_cap_met(ray, cy, t_bot, t_))
	{
		if (t_bot < 0)
			return (0);
	}
	else if (is_cap_met(ray, cy, t_top, t_))
	{
		if (t_top < 0)
			return (0);
	}
	else
		return (0);
	return (1);
}

void	discriminant_cy_2(t_ray *ray, t_cyl *cy, t_eq_param *eq_sys)
{
	float	dr[3];
	float	s1;
	float	s2;

	dr[0] = ray->dir.x;
	dr[1] = ray->dir.y;
	dr[2] = ray->dir.z;
	eq_sys->a = powf(dr[0], 2) + powf(dr[2], 2);
	eq_sys->b = 2 * ray->origin.x * dr[0] + \
		2 * ray->origin.z * dr[2];
	eq_sys->c = powf(ray->origin.x, 2) + powf(ray->origin.z, 2) - \
		powf(cy->radius, 2);
	(*eq_sys).delta = (powf(eq_sys->b, 2) - 4 * eq_sys->a * eq_sys->c);
	s1 = (-(*eq_sys).b + sqrtf((*eq_sys).delta)) / (2 * (*eq_sys).a);
	s2 = (-(*eq_sys).b - sqrtf((*eq_sys).delta)) / (2 * (*eq_sys).a);
	if (fabs(ray->origin.y + s1 * ray->dir.y) > cy->height
		&& fabs(ray->origin.y + s2 * ray->dir.y) > cy->height)
		(*eq_sys).delta = -1;
}

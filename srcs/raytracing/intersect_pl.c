/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_pl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 12:02:08 by mababou           #+#    #+#             */
/*   Updated: 2022/05/04 15:06:41 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

// warning: the ray needs to be normalized
int	intersection_pt_pl(t_ray *ray, t_plan *pl, t_3D_point *pt)
{
	int	disc[2];

	disc[0] = scalar(pl->normal, vector(pl->point, ray->origin));
	disc[1] = scalar(pl->normal, ray->dir);
	if (disc[1] == 0 || disc[0] == 0)
		return (0);
	set_point(pt, ray->origin.x + (disc[0] / disc[1]) * ray->dir.x,
		ray->origin.y + (disc[0] / disc[1]) * ray->dir.y,
		ray->origin.z + (disc[0] / disc[1]) * ray->dir.z);
	return (1);
}

// get info about intersection with a given object (sphere here)
void	analyze_ray_for_plan(t_ray *ray, t_plan *pl, int *color)
{
	t_data		*data;
	t_3D_point	pt;

	set_point(&pt, 0, 0, 0);
	data = get_data(0, 0);
	if (intersection_pt_pl(ray, pl, &pt))
	{
		// TODO calc distance, backup nearest color, 
		// if distance smaller replace color

		// Ambiant light
		*color = rgb_ambiant(arr_to_rgb(pl->rgb), \
			data->amb->rgb, data->amb->grad);
		// spot ?
	}
}

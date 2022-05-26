/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_cy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 21:06:35 by mababou           #+#    #+#             */
/*   Updated: 2022/05/26 21:14:42 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	get_color_cyl(t_ray *ray, t_cyl *cy, int *color, float *distance)
{
	t_data		*data;
	t_impact	impact;
	t_ray		norm;

	float	v;
	float	dist;
	int		ret;

	data = get_data(0, 0);
	ret = intersection_impact_cy(ray, cy, &impact);
	if (ret)
	{
		dist = distance_3d(data->cam->pov, impact.pt);
		if (dist > *distance && *distance >= 0)
			return ;
		*distance = dist;
		*color = rgb_ambiant(arr_to_rgb(impact.rgb), \
			data->amb->rgb, data->amb->grad);

		set_point(&norm.origin, impact.pt.x, impact.pt.y, impact.pt.z);
		set_vector(&norm.dir, impact.pt.x - cy->point.x, \
				impact.pt.y - cy->point.y, \
				impact.pt.z - cy->point.z);

		if (ret == 2)
		{
			v = vec_dot(cy->dir, norm.dir);
			if (v > 0)
			{
				norm.dir.x = cy->dir.x;
				norm.dir.y = cy->dir.y;
				norm.dir.z = cy->dir.z;
			}
			else
			{
				norm.dir.x = -cy->dir.x;
				norm.dir.y = -cy->dir.y;
				norm.dir.z = -cy->dir.z;
			}
		}
		else
		{
			v = vec_dot(cy->dir, norm.dir);
			norm.dir.x -= v * cy->dir.x;
			norm.dir.y -= v * cy->dir.y;
			norm.dir.z -= v * cy->dir.z;
		}
		normalize_v(&norm.dir);
		*color = add_color(*color, \
						calc_spot(&norm, ray, data->light_lst, impact.rgb));

	}
}

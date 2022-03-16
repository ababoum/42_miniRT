/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3D_sphere.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 18:49:35 by mababou           #+#    #+#             */
/*   Updated: 2022/03/16 18:57:11 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	draw_sp(t_data *data)
{
	t_sphere	*sp;
	t_ray		ray;
	int			i;

	sp = data->obj_lst->ptr;
	ray.origin = data->cam->POV;
	i = 0;
	while (i < WIN_WIDTH * WIN_HEIGHT)
	{
		ray.dir.x = (i % WIN_WIDTH) / 100.0;
		ray.dir.y = (i / WIN_WIDTH) / 100.0;
		if (intersect_sp(&ray, sp))
			pixel_put(data, i % WIN_WIDTH, i / WIN_WIDTH, RGB_to_int(sp->RGB));
		else
			pixel_put(data, i % WIN_WIDTH, i / WIN_WIDTH, \
				RGB_to_int(data->amb->RGB));
		i++;
	}
}

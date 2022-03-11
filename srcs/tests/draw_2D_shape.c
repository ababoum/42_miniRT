/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2D_shape.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 18:49:33 by mababou           #+#    #+#             */
/*   Updated: 2022/03/11 14:02:52 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	draw_circle(t_data *data, t_2D_point center, float radius)
{
	t_2D_point	pixel;
	int			i;

	pixel.x = 0;
	pixel.y = 0;
	i = 0;
	while (i < WIN_WIDTH * WIN_HEIGHT)
	{
		pixel.x = i % WIN_WIDTH;
		pixel.y = i / WIN_WIDTH;
		if (distance_2D(pixel, center) <= radius)
			pixel_put(data, pixel.x, pixel.y, RED);
		i++;
	}
}

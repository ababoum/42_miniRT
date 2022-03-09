/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2D_shape.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 18:49:33 by mababou           #+#    #+#             */
/*   Updated: 2022/03/09 18:57:45 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	draw_circle(t_data *data, float x_center, float y_center, float radius)
{
	int	x;
	int	y;
	
	x = 0;
	y = 0;
	while (x < WIN_WIDTH)
	{
		y = 0;
		while (y < WIN_HEIGHT)
		{
			if (distance())
			{
				pixel_put(data, x, y, RED);
			}
			y++;
		}
		x++;
	}
}
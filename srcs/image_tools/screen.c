/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 16:37:51 by mababou           #+#    #+#             */
/*   Updated: 2022/05/08 15:42:52 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

// the X and Y are switched because the axis 
void	pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;
	t_img	*img;
	int		x_img;
	int		y_img;

	x_img = x;
	y_img = WIN_HEIGHT - y;
	img = data->img;
	dst = img->addr + (y_img * img->line_length + \
						x_img * (img->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}

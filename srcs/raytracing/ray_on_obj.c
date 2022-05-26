/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_on_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 11:47:25 by mababou           #+#    #+#             */
/*   Updated: 2022/05/26 21:10:19 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"
#include "../../minilibx-linux/mlx_int.h"

// get info about intersection with a given object

static int	calc_coord(int x, int y)
{
	x %= TEXTURE_SIZE;
	y %= TEXTURE_SIZE;
	if (x < 0)
		x += TEXTURE_SIZE;
	if (y < 0)
		y += TEXTURE_SIZE;
	return (y * 512 + x);
}

void	get_h(int *x, int *y, unsigned char *texture)
{
	int	lx;
	int	ly;
	int	sx;
	int	sy;

	lx = *x;
	ly = *y;
	sx = texture[calc_coord(lx - 1, ly + 1)] / 2 + \
			texture[calc_coord(lx - 1, ly)] + \
			texture[calc_coord(lx - 1, ly - 1)] / 2 - \
			texture[calc_coord(lx + 1, ly + 1)] / 2 - \
			texture[calc_coord(lx + 1, ly)] - \
			texture[calc_coord(lx + 1, ly - 1)] / 2;
	sy = texture[calc_coord(lx - 1, ly + 1)] / 2 + \
			texture[calc_coord(lx, ly + 1)] + \
			texture[calc_coord(lx + 1, ly + 1)] / 2 - \
			texture[calc_coord(lx - 1, ly - 1)] / 2 - \
			texture[calc_coord(lx, ly - 1)] - \
			texture[calc_coord(lx + 1, ly - 1)] / 2;
	*x = sx;
	*y = -sy;
}

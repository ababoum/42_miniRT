/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 17:15:48 by mababou           #+#    #+#             */
/*   Updated: 2022/05/25 18:47:02 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	check_int_color(char *message, int rgb[3])
{
	t_data	*data;

	data = get_data(0, 0);
	if (rgb[0] < 0 || rgb[0] > 255 || \
		rgb[1] < 0 || rgb[1] > 255 || \
		rgb[2] < 0 || rgb[2] > 255)
		exit_message(data, message, EXIT_FAILURE);
}

int	rgb_to_int(int rgb[3])
{
	return (0x10000 * rgb[0] + 0x100 * rgb[1] + rgb[2]);
}

int	add_color(int rgb1, int rgb2)
{
	int	r;
	int	g;
	int	b;

	r = rgb1 % 256 + rgb2 % 256;
	g = (rgb1 / 256) % 256 + (rgb2 / 256) % 256;
	b = (rgb1 / 65536) % 256 + (rgb2 / 65536) % 256;
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	return (r + g * 256 + b * 65536);
}

int	rgb_factor(int rgb, float factor)
{
	int	r;
	int	g;
	int	b;

	r = rgb % 256;
	g = (rgb / 256) % 256;
	b = (rgb / 65536) % 256;
	r *= factor;
	g *= factor;
	b *= factor;
	return (r + g * 256 + b * 65536);
}

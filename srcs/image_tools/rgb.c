/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 14:38:39 by mababou           #+#    #+#             */
/*   Updated: 2022/05/04 14:39:57 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// Created by plefevre on 4/25/22.
//

int	arr_to_rgb(int *rgb)
{
	return (rgb[2] + rgb[1] * 256 + rgb[0] * 65536);
}

int	rgb_ambiant(int rgb, int *amb_rgb, float grad)
{
	int	r;
	int	g;
	int	b;

	r = (rgb / 65536) % 256;
	g = (rgb / 256) % 256;
	b = rgb % 256;
	r *= grad * amb_rgb[0] / 256;
	g *= grad * amb_rgb[1] / 256;
	b *= grad * amb_rgb[2] / 256;
	return (b + g * 256 + r * 65536);
}

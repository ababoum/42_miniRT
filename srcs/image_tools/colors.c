/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 17:15:48 by mababou           #+#    #+#             */
/*   Updated: 2022/03/22 14:46:07 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int	check_int_color(int rgb[3])
{
	if (rgb[0] < 0 || rgb[0] > 255 || \
		rgb[1] < 0 || rgb[1] > 255 || \
		rgb[2] < 0 || rgb[2] > 255)
		return (0);
	return (1);
}

int	rgb_to_int(int rgb[3])
{
	return (0xFFFF * rgb[0] + 0xFF * rgb[1] + rgb[2]);
}

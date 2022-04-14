/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atof.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 19:12:12 by mababou           #+#    #+#             */
/*   Updated: 2022/04/14 14:55:17 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static void	add_decimal_part(char *str, float *output)
{
	int	i;

	i = 0;
	if (str[i] != '.')
		return ;
	i++;
	while (ft_isdigit(str[i]))
	{
		*output += (str[i] - '0') * powf(10, -i);
		i++;
	}
}

float	ft_atof(char *str)
{
	int		i;
	int		sign;
	float	output;

	i = 0;
	output = 0.0;
	sign = 1;
	while (is_char(str[i], SPACES))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
		output = output * 10 + (str[i++] - '0');
	add_decimal_part(str + i, &output);
	return (sign * output);
}

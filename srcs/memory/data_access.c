/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_access.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 14:48:48 by mababou           #+#    #+#             */
/*   Updated: 2022/04/14 14:49:04 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_data	*get_data(int code, t_data *input)
{
	static t_data	*data_ptr;

	if (code == 0)
		return (data_ptr);
	else
	{
		data_ptr = input;
		return (0);
	}
}

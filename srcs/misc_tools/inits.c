/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 18:47:41 by mababou           #+#    #+#             */
/*   Updated: 2022/04/14 16:50:58 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	data_init(t_data *data, const char *path)
{
	get_data(!0, data);
	data->mem_lst = 0;
	data->obj_lst = 0;
	data->amb = 0;
	data->cam = 0;
	data->lum = 0;
	data->session = 0;
	data->win = 0;
	parse_input(data, path);
}

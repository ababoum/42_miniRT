/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 18:47:41 by mababou           #+#    #+#             */
/*   Updated: 2022/03/16 19:05:09 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	data_init(t_data *data, const char *path)
{
	data->mem_lst = 0;
	data->obj_lst = 0;
	data->amb = malloc_log(data, sizeof(t_ambiance));
	data->cam = malloc_log(data, sizeof(t_camera));
	data->lum = malloc_log(data, sizeof(t_light));
	data->session = 0;
	data->win = 0;
	parse_input(data, path);
}

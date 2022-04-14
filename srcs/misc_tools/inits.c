/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 18:47:41 by mababou           #+#    #+#             */
/*   Updated: 2022/04/14 16:15:02 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

// static void	pop_fn_init(t_data *data)
// {
// 	data->pop_fn[0] = populate_amb;
// 	data->pop_fn[1] = populate_cam;
// 	data->pop_fn[2] = populate_light;
// 	data->pop_fn[3] = populate_sphere;
// 	data->pop_fn[4] = populate_plan;
// 	data->pop_fn[5] = populate_cyl;
// }

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
	// pop_fn_init(data);
	parse_input(data, path);
}

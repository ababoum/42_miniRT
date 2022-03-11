/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 19:38:50 by mababou           #+#    #+#             */
/*   Updated: 2022/03/11 12:01:17 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	main(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (EXIT_FAILURE);
	data_init(data);
	mlx_start(data);
	img_init(data);
	draw_circle(data, 0, 0, 500);
	mlx_put_image_to_window(data->session, data->win, data->img->ptr, 0, 0);
	mlx_events(data);
	mlx_loop(data->session);
}

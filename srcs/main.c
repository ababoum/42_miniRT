/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 19:38:50 by mababou           #+#    #+#             */
/*   Updated: 2022/03/11 18:03:33 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac != 2)
	{
		ft_putstr_fd("Please have one input with .rt extension\n", 2);
		return (EXIT_FAILURE);
	}
	data = malloc(sizeof(t_data));
	if (!data)
		return (EXIT_FAILURE);
	data_init(data, av[1]);
	mlx_start(data);
	img_init(data);
	draw_circle(data, point_2D(500, 500), 500);
	mlx_put_image_to_window(data->session, data->win, data->img->ptr, 0, 0);
	mlx_events(data);
	mlx_loop(data->session);
}

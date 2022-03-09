/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 16:48:05 by mababou           #+#    #+#             */
/*   Updated: 2022/03/09 18:41:10 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	mlx_start(t_data *data)
{
	void	*mlx;

	mlx = mlx_init();
	data->session = mlx;
	data->win = mlx_new_window(mlx, WIN_WIDTH, WIN_HEIGHT, "Raytracing");
}

void	img_init(t_data *data)
{
	t_img	*img;

	img = malloc_log(data, sizeof(t_img));
	data->img = img;
	img->ptr = mlx_new_image(data->session, WIN_WIDTH, WIN_HEIGHT);
	img->addr = mlx_get_data_addr(img->ptr, &img->bits_per_pixel, \
		&img->line_length, &img->endian);
}

void	data_init(t_data *data)
{
	data->mem_lst = 0;
}

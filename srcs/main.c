/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 19:38:50 by mababou           #+#    #+#             */
/*   Updated: 2022/06/14 12:13:21 by plefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

// the matrix is used to set the casted rays as coming from the camera
static void	prepare_camera_mat(t_data *data, t_m4 *mat)
{
	float	rot_angles[2];

	set_identity(mat);
	translate_mat(mat, data->cam->pov.x, \
		data->cam->pov.y, data->cam->pov.z);
	rot_angles[0] = get_angle(data->cam->dir.y, data->cam->dir.x);
	rot_angles[1] = get_angle(sqrtf(data->cam->dir.x * data->cam->dir.x + \
		data->cam->dir.y * data->cam->dir.y), \
		data->cam->dir.z);
	rotate_z_mat(mat, rot_angles[0]);
	rotate_x_mat(mat, rot_angles[1]);
}

int	transform_pixel(int i)
{
	int	line_b;
	int	square;
	int	x_square;
	int	y_square;

	line_b = (i / (RENDERING_Q * WIN_WIDTH)) * (RENDERING_Q * WIN_WIDTH);
	square = (i - line_b) / (RENDERING_Q * RENDERING_Q) * RENDERING_Q;
	x_square = i % RENDERING_Q;
	y_square = i % (RENDERING_Q * RENDERING_Q) / RENDERING_Q;
	return (line_b + square + WIN_WIDTH * y_square + x_square);
}

void	draw_data(t_data *data, int start, int end)
{
	t_m4	mat;
	int		i;
	int		j;
	int		color;

	prepare_camera_mat(data, &mat);
	i = start;
	while (i < end)
	{
		j = 0;
		color = compute_pixel_color(transform_pixel(i), data, mat);
		while (j < RENDERING_Q * RENDERING_Q)
		{
			pixel_put(data, transform_pixel(i) % WIN_WIDTH, \
			transform_pixel(i) / WIN_WIDTH, color);
			i++;
			j++;
		}
	}
}

int	render(t_data *data)
{
	static int	i = 0;

	if (i < WIN_HEIGHT * WIN_WIDTH + 1)
	{
		draw_data(data, i, i + WIN_WIDTH);
		i += WIN_WIDTH;
		mlx_put_image_to_window(data->session, data->win, data->img->ptr, 0, 0);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac != 2)
	{
		ft_putstr_fd(RED_TXT, 2);
		ft_putstr_fd("Error\nPlease have one input with .rt extension\n", 2);
		ft_putstr_fd(RESET_TXT, 2);
		return (EXIT_FAILURE);
	}
	data = malloc(sizeof(t_data));
	if (!data)
		return (EXIT_FAILURE);
	data_init(data, av[1]);
	mlx_events(data);
	mlx_loop_hook(data->session, render, data);
	mlx_loop(data->session);
	return (0);
}

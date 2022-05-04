/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 19:38:50 by mababou           #+#    #+#             */
/*   Updated: 2022/05/04 18:14:48 by mababou          ###   ########.fr       */
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
	rot_angles[0] = get_angle(data->cam->dir.x, data->cam->dir.y);
	rot_angles[1] = get_angle(sqrtf(data->cam->dir.x * data->cam->dir.x + \
						data->cam->dir.y * data->cam->dir.y), \
						data->cam->dir.z);
	rotate_y_mat(mat, rot_angles[0]);
	rotate_x_mat(mat, rot_angles[1]);
}

void	draw_data(t_data *data)
{
	t_ray	ray;
	t_m4	mat;
	int		i;

	prepare_camera_mat(data, &mat);
	i = 0;
	while (i < WIN_WIDTH * WIN_HEIGHT)
	{
		prepare_initial_ray(&ray, data, i, mat);
		pixel_put(data, i % WIN_WIDTH, i / WIN_WIDTH, \
			compute_pixel_color(&ray, data));
		i++;
	}
	printf("Image ready\n");
}

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
	draw_data(data);
	mlx_put_image_to_window(data->session, data->win, data->img->ptr, 0, 0);
	mlx_events(data);
	mlx_loop(data->session);
}

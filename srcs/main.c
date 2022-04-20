/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 19:38:50 by mababou           #+#    #+#             */
/*   Updated: 2022/04/14 16:32:01 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void set_3d_point(t_3D_point *pt, float x, float y, float z)
{
	pt->x = x;
	pt->y = y;
	pt->z = z;
}

void draw_data(t_data *data)
{
	t_ray ray;
	ray.origin = dot_3d(0, 0, 0);
	ray.dir = dot_3d(0, 0, 0);


	for (int i = 0; i < WIN_WIDTH * WIN_HEIGHT; ++i)
	{
		//calculate ray
		//position "ecran"
		float x_ecran = (i % WIN_WIDTH * 1.0) / WIN_WIDTH * 2.0 - 1;
		float y_ecran = (i / WIN_WIDTH * 1.0) / WIN_HEIGHT * 2.0 - 1;


		set_3d_point(ray.origin, x_ecran, 0, y_ecran);
		set_3d_point(ray.origin, x_ecran * 10, 1, y_ecran * 10);

		t_obj *objs = data->obj_lst;

		int color = 0;

		while (objs)
		{
			if (objs->type == 0)
			{
				t_sphere *sp = (t_sphere *)objs->ptr;
				if (intersect_sp(&ray, sp))
				{
					color = 1000;
				}
			}
			objs = objs->next;
		}


		(void) ray;
		pixel_put(data, i % WIN_WIDTH, i / WIN_WIDTH, color);
	}


	printf("Image ready\n");


}

int main(int ac, char **av)
{
	t_data *data;

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
//	draw_circle(data, dot_2d(500, 500), 500);
//	draw_sp(data);
	mlx_put_image_to_window(data->session, data->win, data->img->ptr, 0, 0);
	mlx_events(data);
	mlx_loop(data->session);
}

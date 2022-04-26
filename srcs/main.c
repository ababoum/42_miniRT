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


int rgb_factor(int rgb, float factor)
{
	int r;
	int g;
	int b;

	r = rgb % 256;
	g = (rgb / 256) % 256;
	b = (rgb / 65536) % 256;
	r *= factor;
	g *= factor;
	b *= factor;

	return (r + g * 256 + b * 65536);
}

int add_color(int rgb1, int rgb2)
{
	int r;
	int g;
	int b;

	r = rgb1 % 256 + rgb2 % 256;
	g = (rgb1 / 256) % 256 + (rgb2 / 256) % 256;
	b = (rgb1 / 65536) % 256 + (rgb2 / 65536) % 256;

	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	return (r + g * 256 + b * 65536);
}

int calc_spot(t_ray *norm, t_light *light, int *rgb)
{
	t_3D_point pt;
	float	f;
	int		color;

	pt.x = light->src->x - norm->origin->x;
	pt.y = light->src->y - norm->origin->y;
	pt.z = light->src->z - norm->origin->z;

	normalize(&pt);
	f = pt.x * norm->dir->x
			+ pt.y * norm->dir->y
			+ pt.z * norm->dir->z;

	if (f < 0)
		f = 0;
	color = (rgb_ambiant(arr_toRGB(rgb),light->rgb, f *light->pow));
	//specular
	if (f >= 0.98f)
	{
		f = (f-0.98f)/0.02f;
		color = add_color(color, rgb_ambiant(arr_toRGB(light->rgb), light->rgb,f * light->pow));
	}

	return (color);
}



void draw_data(t_data *data)
{
	t_ray ray;
	t_3D_point pt;
	t_ray norm;
	int i;


	ray.dir = dot_3d(0, 0, 0);
	ray.origin = dot_3d(0, 0, 0);
	norm.dir = dot_3d(0, 0, 0);
	norm.origin = dot_3d(0, 0, 0);

	i = 0;

	while (i < WIN_WIDTH * WIN_HEIGHT)
	{
		//calculate ray
		//position "ecran"
		//A voir si c'est vraiment utile ou si on peut juste partir de 0,0,0
		float ratio = WIN_HEIGHT * 1.0f / WIN_WIDTH;
		float x_ecran = (i % WIN_WIDTH * 1.0f) / WIN_WIDTH * 2.0f - 1;
		float y_ecran =
				((i / WIN_WIDTH * 1.0f) / WIN_HEIGHT * 2.0f - 1) * ratio;

//		x_ecran= 0;
//		y_ecran= 0;
//TODO check FOV
		set_3d_point(ray.origin, x_ecran * 0, 0, y_ecran * 0);
		set_3d_point(ray.dir, x_ecran * 1.0f, 1/ tanf(0.5f * data->cam->fov * 2 * M_PI / 180.0), y_ecran * 1.0f);

		normalize(ray.dir);

		t_obj *objs = data->obj_lst;

		int color = 0;

		while (objs)
		{
			if (objs->type == 0)
			{
				t_sphere *sp = (t_sphere *) objs->ptr;

				if (intersection_pt_sp(&ray, sp, &pt))
				{

					//Ambiant light
					color = rgb_ambiant(arr_toRGB(sp->rgb), data->amb->rgb, data->amb->grad);

					//spot
					norm.origin->x = pt.x;
					norm.origin->y = pt.y;
					norm.origin->z = pt.z;

					norm.dir->x = pt.x - sp->center->x;
					norm.dir->y = pt.y - sp->center->y;
					norm.dir->z = pt.z - sp->center->z;


					normalize(norm.dir);

					color = add_color(color, calc_spot(&norm, data->lum, sp->rgb));


					//Pour faire les calculs de lumiere il faudrait avoir la position de l'intersection du rayon et de la sphere

				}
			}
			objs = objs->next;
		}


		(void) ray;
		pixel_put(data, i % WIN_WIDTH, i / WIN_WIDTH, color);
		i++;
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

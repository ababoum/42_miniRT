/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 19:38:50 by mababou           #+#    #+#             */
/*   Updated: 2022/04/27 19:48:53 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"
#include "../includes/ft3d.h"

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

float ffabs(float f)
{
	if (f < 0)
		return (-f);
	return (f);
}

int test_middle_f(float f1, float f2, float f3)
{
	return ((f1 >= f2 && f2 >= f3) || (f1 <= f2 && f2 <= f3));
}

//test if p2 is beetween p2 and p3
int test_middle(t_3D_point *p1, t_3D_point *p2, t_3D_point *p3)
{
	return (test_middle_f(p1->x, p2->x, p3->x)
		&& test_middle_f(p1->y, p2->y, p3->y)
		&& test_middle_f(p1->z, p2->z, p3->z));
}

int object_between(t_3D_point *p1, t_3D_point *p2,t_ray  *ray, t_data *data)
{
	(void) p1;
	(void) p2;
	(void) data;

	t_obj *objs = data->obj_lst;

	while (objs)
	{
		if (objs->type == 0)
		{
			t_sphere *sp = (t_sphere *) objs->ptr;
			t_3D_point pt;

			projection_pt_droite(ray, sp->center, &pt);
//			if (distance_3d(&pt,sp->center) < sp->radius && test_middle(p1, &pt, p2))
			if (test_middle(p1, &pt, p2))
				return (1);
		}
		objs = objs->next;
	}

	return (0);
}

int calc_spot(t_ray *norm, t_ray *ray, t_light *light, int *rgb, t_data *data)
{
	t_3D_point vec;
	float f;
	int color;

	vec.x = light->src->x - norm->origin->x;
	vec.y = light->src->y - norm->origin->y;
	vec.z = light->src->z - norm->origin->z;

	if (object_between(light->src, norm->origin,ray, data))
		return (0);

	normalize(&vec);
	f = vec.x * norm->dir->x
		+ vec.y * norm->dir->y
		+ vec.z * norm->dir->z;

	if (f < 0)
		f = 0;
	color = (rgb_ambiant(arr_toRGB(rgb), light->rgb, f * light->pow));
	//specular
	if (f >= 0.98f)
	{
		f = (f - 0.98f) / 0.02f;
		color = add_color(color, rgb_ambiant(arr_toRGB(light->rgb), light->rgb,
											 f * light->pow));
	}

	return (color);
}



float getAngle(float dx, float dy)
{
	float a;

	a = atanf(ffabs(dy) / ffabs(dx));

	if (dx > 0 && dy > 0)
		return a;

	if (dx < 0 && dy > 0)
		return -a + (float) M_PI;

	if (dx < 0 && dy < 0)
		return a + (float) M_PI;

	if (dx > 0 && dy < 0)
		return -a + 2 * (float) M_PI;


	if (dy == 0)
		return (float) (dx < 0 ? M_PI : 0);
	if (dx == 0)
		return (float) (dy > 0 ? M_PI / 2 : 3 * M_PI / 2);

	//Inutile mais demandé...
	return 0;
}

float toDeg(float angle)
{
	return ((float) (angle / 2 / M_PI * 180.0));
}

void draw_data(t_data *data)
{
	t_ray ray;
	t_3D_point pt;
	t_ray norm;
	t_m4 mat;
	int i;


	ray.dir = dot_3d(0, 0, 0);
	ray.origin = dot_3d(0, 0, 0);
	norm.dir = dot_3d(0, 0, 0);
	norm.origin = dot_3d(0, 0, 0);

	set_identity(&mat);
	translate_mat(&mat, data->cam->pov->x,
				  data->cam->pov->y,
				  data->cam->pov->z);
	//TODO calc angle and rotate matrix with

	float a1 = getAngle(data->cam->dir->x, data->cam->dir->y);
	float a2 = getAngle(sqrtf(data->cam->dir->x * data->cam->dir->x +
									data->cam->dir->y * data->cam->dir->y),
							  data->cam->dir->z);

	rotate_y_mat(&mat, a1);
	rotate_x_mat(&mat, a2);


	i = 0;
	while (i < WIN_WIDTH * WIN_HEIGHT)
	{
		float ratio = WIN_HEIGHT * 1.0f / WIN_WIDTH;
		float x_ecran = (i % WIN_WIDTH * 1.0f) / WIN_WIDTH * 2.0f - 1;
		float y_ecran =
				((i / WIN_WIDTH * 1.0f) / WIN_HEIGHT * 2.0f - 1) * ratio;

		//TODO check FOV




		set_3d_point(ray.origin, 0, 0, 0);
		set_3d_point(ray.dir, x_ecran * 1.0f,
					 1 / tanf(0.5f * data->cam->fov * 2 * M_PI / 180.0),
					 y_ecran * 1.0f);
		ray_mult_mat(&ray, mat);

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
					//TODO calc distance, backup nearest color, if distance smaller replace color

					//Ambiant light
					color = rgb_ambiant(arr_toRGB(sp->rgb), data->amb->rgb,
										data->amb->grad);
					//spot
					norm.origin->x = pt.x;
					norm.origin->y = pt.y;
					norm.origin->z = pt.z;

					norm.dir->x = pt.x - sp->center->x;
					norm.dir->y = pt.y - sp->center->y;
					norm.dir->z = pt.z - sp->center->z;

					normalize(norm.dir);

					color = add_color(color,
									  calc_spot(&norm,&ray, data->lum, sp->rgb,
												data));

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
	mlx_put_image_to_window(data->session, data->win, data->img->ptr, 0, 0);
	mlx_events(data);
	mlx_loop(data->session);
}

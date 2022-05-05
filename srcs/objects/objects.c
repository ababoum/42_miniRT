/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 17:13:31 by mababou           #+#    #+#             */
/*   Updated: 2022/05/05 11:45:03 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_sphere	*new_sphere(t_data *data)
{
	t_sphere	*sphere;

	sphere = malloc_log(data, sizeof(t_sphere));
	obj_add_back(&(data->obj_lst), new_obj(data, sphere, SPHERE));
	return (sphere);
}

t_plan	*new_plan(t_data *data)
{
	t_plan	*plan;

	plan = malloc_log(data, sizeof(t_plan));
	obj_add_back(&(data->obj_lst), new_obj(data, plan, PLAN));
	return (plan);
}

t_cyl	*new_cylinder(t_data *data)
{
	t_cyl	*cylinder;

	cylinder = malloc_log(data, sizeof(t_cyl));
	obj_add_back(&(data->obj_lst), new_obj(data, cylinder, CYLINDER));
	return (cylinder);
}


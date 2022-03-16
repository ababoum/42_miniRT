/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 17:13:31 by mababou           #+#    #+#             */
/*   Updated: 2022/03/16 17:17:16 by mababou          ###   ########.fr       */
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 16:15:19 by mababou           #+#    #+#             */
/*   Updated: 2022/05/08 16:17:57 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_cone	*new_cone(t_data *data)
{
	t_cone	*cone;

	cone = malloc_log(data, sizeof(t_cone));
	cone->texture=0;
	obj_add_back(&(data->obj_lst), new_obj(data, cone, CONE));
	return (cone);
}

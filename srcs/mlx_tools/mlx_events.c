/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 12:01:27 by mababou           #+#    #+#             */
/*   Updated: 2022/03/11 12:28:24 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int	key_hook(int keycode, t_data *data)
{
	if (keycode == ESC_KEY)
		clear_exit(data, EXIT_SUCCESS);
}

void	mlx_events(t_data *data)
{
	mlx_key_hook(data->win, key_hook, data);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 12:01:27 by mababou           #+#    #+#             */
/*   Updated: 2022/04/14 14:37:37 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int	key_hook(int keycode, t_data *data)
{
	if (keycode == ESC_KEY)
		clear_exit(data, EXIT_SUCCESS);
	return (0);
}

int	exit_hook(t_data *data)
{
	clear_exit(data, EXIT_SUCCESS);
	return (0);
}

void	mlx_events(t_data *data)
{
	mlx_key_hook(data->win, key_hook, data);
	mlx_hook(data->win, X_CLOSE, 0, exit_hook, data);
}

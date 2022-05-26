/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 16:13:34 by mababou           #+#    #+#             */
/*   Updated: 2022/05/08 16:24:09 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	check_line_args_bonus(t_data *data, char *type, int argc)
{
	if (!ft_strcmp(type, "Cone") && argc != 4 && argc != 5 && argc != 6)
	{
		ft_putstr_fd("Cone: ", STDERR_FILENO);
		exit_message(data, "Incorrect number of parameters", EXIT_FAILURE);
	}
}

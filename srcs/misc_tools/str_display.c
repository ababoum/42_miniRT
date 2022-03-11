/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_display.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 17:58:28 by mababou           #+#    #+#             */
/*   Updated: 2022/03/11 18:12:41 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	ft_putstr_fd(char *str, int fd)
{
	if (write(fd, str, ft_strlen(str)) == -1)
		perror(str);
}

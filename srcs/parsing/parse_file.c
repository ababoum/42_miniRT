/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 17:44:24 by mababou           #+#    #+#             */
/*   Updated: 2022/03/11 18:15:29 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	parse_line(t_data *data, char *line)
{
	(void)line;
	(void)data;
}

void	parse_input(t_data *data, const char *path)
{
	int		fd;
	char	*line;
	
	fd = verify_file(data, path);
	line = get_next_line(fd);
	while (line)
	{
		parse_line(data, line);
		free(line);
		line = get_next_line(fd);
	}
}

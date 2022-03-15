/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 17:44:24 by mababou           #+#    #+#             */
/*   Updated: 2022/03/15 14:57:16 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static void parse_line_redir(t_data *data, char *line, char *type, int i)
{
	if (!ft_strcmp(type, "A"))
		populate_amb(data, line + i);
	else if (!ft_strcmp(type, "C"))
		populate_cam(data, line + i);
	else if (!ft_strcmp(type, "L"))
		populate_light(data, line + i);
	else if (!ft_strcmp(type, "sp"))
		populate_sphere(data, line + i);
	else if (!ft_strcmp(type, "pl"))
		populate_plan(data, line + i);
	else if (!ft_strcmp(type, "cy"))
		populate_cyl(data, line + i);
	else
		exit_message(data, "Wrong object type in the file\n", EXIT_FAILURE);
}

void	parse_line(t_data *data, char *line)
{
	int		i;
	char	*type;

	i = 0;
	while (is_char(line[i], " \t"))
		i++;
	type = ft_split(data, line, " \t")[0];
	i += ft_strlen(type);
	while (is_char(line[i], " \t"))
		i++;
	parse_line_redir(data, line, type, i);
}

void	parse_input(t_data *data, const char *path)
{
	int		fd;
	char	*line;
	
	fd = verify_file(data, path);
	line = get_next_line(fd);
	while (line)
	{
		if (*line != '\n')
			parse_line(data, line);
		free(line);
		line = get_next_line(fd);
	}
}

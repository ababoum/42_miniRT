/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 17:44:24 by mababou           #+#    #+#             */
/*   Updated: 2022/04/14 17:01:29 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static void	parse_line_redir(t_data *data, char *line, char *type, int i)
{
	size_t			index;
	const char		*obj_names[] = {"A", "C", "L", "sp", "pl", "cy"};
	const t_pop_fn	pop_fn_lst[] = {
		populate_amb, populate_cam, populate_light, \
		populate_sphere, populate_plan, populate_cyl \
	};

	index = 0;
	while (index < sizeof(obj_names) / sizeof(char *))
	{
		if (!ft_strcmp(type, obj_names[index]))
		{
			pop_fn_lst[index](data, line + i);
			return ;
		}
		index++;
	}
	exit_message(data, "Unrecognized object type in the file\n", EXIT_FAILURE);
}

void	parse_line(t_data *data, char *line)
{
	int		i;
	char	*type;

	i = 0;
	while (is_char(line[i], SPACES))
		i++;
	type = ft_split(data, line, SPACES)[0];
	i += ft_strlen(type);
	while (is_char(line[i], SPACES))
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

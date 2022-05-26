/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 17:44:24 by mababou           #+#    #+#             */
/*   Updated: 2022/05/26 15:03:45 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static void	parse_line_redir(t_data *data, char *line, char *type, int i)
{
	size_t			index;
	const char		*obj_names[] = {"A", "C", "L", "sp", "pl", "cy", "cn"};
	const t_pop_fn	pop_fn_lst[] = {
		populate_amb, populate_cam, populate_light, \
		populate_sphere, populate_plan, populate_cyl, populate_cn \
	};

	index = 0;
	while (index < sizeof(obj_names) / sizeof(char *))
	{
		if (!ft_strcmp(type, "cn") && !BONUS_ON)
			break ;
		if (!ft_strcmp(type, obj_names[index]))
		{
			pop_fn_lst[index](data, line + i);
			return ;
		}
		index++;
	}
	exit_message(data, "Unrecognized object type in the file", EXIT_FAILURE);
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
	mem_add_back(&(data->mem_lst), new_mem(data, line, MEM_TYPE));
	while (line)
	{
		if (*line != '\n' && *line != '#' && *line != '\n')
			parse_line(data, line);
		line = get_next_line(fd);
		mem_add_back(&(data->mem_lst), new_mem(data, line, MEM_TYPE));
	}
	if (!data->cam)
		exit_message(data, "Camera needed in the input file", EXIT_FAILURE);
	if (!data->amb)
		exit_message(data, "Ambiance needed in the input file", EXIT_FAILURE);
	if (!data->light_lst)
		exit_message(data, "Light needed in the input file", EXIT_FAILURE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 16:56:37 by mababou           #+#    #+#             */
/*   Updated: 2022/03/09 17:38:52 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static void	ft_lstclear(t_data *data)
{
	t_memlog	*tmp;
	t_memlog	*tmp_next;

	tmp = data->mem_lst;
	while (tmp)
	{
		tmp_next = tmp->next;
		if (tmp->type == MEM_TYPE)
			free(tmp->ptr);
		else if (tmp->type == IMG_TYPE)
			mlx_destroy_image(data->session, tmp->ptr);
		free(tmp);
		tmp = tmp_next;
	}
	data->mem_lst = NULL;
	free(data);
	data = 0;
}

void	clear_exit(t_data *data, int exit_code)
{
	if (data)
		ft_lstclear(data);
	exit(exit_code);
}

void	exit_message(t_data *data, char *message, int exit_code)
{
	printf("%s\n", message);
	clear_exit(data, exit_code);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 16:56:37 by mababou           #+#    #+#             */
/*   Updated: 2022/05/18 10:52:03 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

// manage the memory freeing at the end of the program or 
// at an error-provoked exit
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
	if (data->session && data->win)
		mlx_destroy_window(data->session, data->win);
	if (data->session)
		mlx_destroy_display(data->session);
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
	ft_putstr_fd(RED_TXT, 2);
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	ft_putstr_fd(RESET_TXT, 2);
	clear_exit(data, exit_code);
}

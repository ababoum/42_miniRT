/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_log.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 16:52:50 by mababou           #+#    #+#             */
/*   Updated: 2022/03/09 17:57:12 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static t_memlog	*new_mem(t_data *data, void *ptr, int type)
{
	t_memlog	*new;

	new = malloc(sizeof(t_memlog));
	if (!new)
		exit_message(data, "Malloc failure", EXIT_FAILURE);
	new->ptr = ptr;
	new->type = type;
	new->next = NULL;
	return (new);
}

static t_memlog	*mem_lstlast(t_memlog *lst)
{
	t_memlog	*tmp;

	tmp = lst;
	while (tmp && tmp->next)
		tmp = tmp->next;
	return (tmp);
}

static void	mem_add_back(t_memlog **alst, t_memlog *new)
{
	t_memlog	*last;

	if (*alst)
	{
		last = mem_lstlast(*alst);
		last->next = new;
	}
	else if (*alst == NULL)
		*alst = new;
}

void	*malloc_log(t_data *data, int size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		exit_message(data, "Malloc failure", EXIT_FAILURE);
	mem_add_back(&(data->mem_lst), new_mem(data, ptr, MEM_TYPE));
	return (ptr);
}

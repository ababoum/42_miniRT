/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 18:42:54 by mababou           #+#    #+#             */
/*   Updated: 2022/03/11 18:45:46 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_obj	*new_obj(t_data *data, void *ptr, int type)
{
	t_obj	*new;

	new = malloc_log(data, sizeof(t_obj));
	new->ptr = ptr;
	new->type = type;
	new->next = NULL;
	return (new);
}

static t_obj	*obj_lstlast(t_obj *lst)
{
	t_obj	*tmp;

	tmp = lst;
	while (tmp && tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	obj_add_back(t_obj **alst, t_obj *new)
{
	t_obj	*last;

	if (*alst)
	{
		last = obj_lstlast(*alst);
		last->next = new;
	}
	else if (*alst == NULL)
		*alst = new;
}

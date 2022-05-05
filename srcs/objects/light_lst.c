/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 15:27:51 by mababou           #+#    #+#             */
/*   Updated: 2022/05/05 16:00:47 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static t_light	*light_lstlast(t_light *lst)
{
	t_light	*tmp;

	tmp = lst;
	while (tmp && tmp->next)
		tmp = tmp->next;
	return (tmp);
}

static void	light_add_back(t_light **alst, t_light *new)
{
	t_light	*last;

	if (*alst)
	{
		last = light_lstlast(*alst);
		last->next = new;
	}
	else if (*alst == NULL)
		*alst = new;
}

t_light	*new_light_src(t_data *data)
{
	t_light	*new;

	new = malloc_log(data, sizeof(t_light));
	new->next = NULL;
	light_add_back(&(data->light_lst), new);
	return (new);
}

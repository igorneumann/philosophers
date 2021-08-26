/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 17:39:36 by ineumann          #+#    #+#             */
/*   Updated: 2021/08/26 17:02:18 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	*ft_lst_last(t_data *elem)
{
	t_data	*old;

	old = elem;
	if (elem)
	{
		while (elem->next && elem->next != old)
			elem = elem->next;
	}
	return (elem);
}

t_data	*ft_lst_first(t_data *elem)
{
	t_data	*old;

	old = elem;
	if (elem)
	{
		while (elem->prev && elem->prev != old)
			elem = elem->prev;
	}
	return (elem);
}

t_data	*remove_elem(t_data *elem)
{
	if (elem->prev && elem->next && elem)
	{
		elem->prev->next = elem->next;
		elem->next->prev = elem->prev;
		elem = elem->prev;
	}
	if (!elem->prev && elem->next && elem)
	{
		elem->next->prev = NULL;
		elem = elem->next;
	}
	if (elem->prev && !elem->next && elem)
	{
		elem->prev->next = NULL;
		elem = elem->prev;
	}
	return (elem);
}

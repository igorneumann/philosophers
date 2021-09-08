/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 20:04:55 by ineumann          #+#    #+#             */
/*   Updated: 2021/09/08 18:40:05 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	*ft_new(int ph_number, uint64_t tm_start, t_main *main)
{
	t_data					*new;

	new = (t_data *)malloc(sizeof(t_data));
	if (!new)
		return (NULL);
	new->prev = NULL;
	new->eaten = 0;
	new->state = 0;
	main->tm_now = get_time();
	new->tm_eat = main->tm_now - tm_start;
	new->number = ph_number;
	new->thread = NULL;
	new->next = NULL;
	new->main = main;
	return (new);
}

void	ft_lst_add(t_data **in, t_data *new)
{
	t_data	*tmp;

	if (!(*in))
	{
		*in = new;
		return ;
	}
	else
	{
		tmp = *in;
		*in = new;
		new->next = tmp;
		if (tmp->prev != NULL)
			new->prev = tmp->prev;
		else if (ft_lst_last(*in) != new)
			new->prev = ft_lst_last(*in);
		tmp->prev = new;
		new->prev->next = new;
		tmp->prev = new;
	}
}

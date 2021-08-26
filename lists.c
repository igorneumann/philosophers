/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 20:04:55 by ineumann          #+#    #+#             */
/*   Updated: 2021/08/26 20:10:54 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	*ft_new(int ph_number)
{
	t_data	*new;

	new = (t_data *)malloc(sizeof(t_data));
	if (!new)
		return (NULL);
	new->prev = NULL;
	new->tm_state = get_time();
	new->eaten = 0;
	new->fork = 1;
	new->state = 0;
	new->number = ph_number;
	new->thread = NULL;
	new->next = NULL;
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

void	ft_lst_edit(t_data **in, t_data *new)
{
	t_data	*tmp;

	tmp = *in;
	new->next = tmp->next;
	new->prev = tmp->prev;
	*in = new;
	free(tmp);
	if (new->next != NULL)
	{
		tmp = new->next;
		tmp->prev = new;
	}
	if (new->prev != NULL)
	{
		tmp = new->prev;
		tmp->next = new;
	}
}

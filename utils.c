/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 20:06:06 by ineumann          #+#    #+#             */
/*   Updated: 2021/08/26 19:42:26 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_data *elem)
{
	t_data	*old;

	old = elem;
	if (elem)
	{
		while (elem->next && elem->next != old)
		{
			if (elem->state == -1)
				return (1);
			elem = elem->next;
		}
	}
	return (0);
}

uint64_t	get_time(void)
{
	struct timeval	end;

	gettimeofday(&end, NULL);
	return ((end.tv_sec * (uint64_t)1000) + (end.tv_usec / 1000));
}

int	ft_atoi(const char *n)
{
	long int	i[3];

	i[0] = 0;
	i[2] = 0;
	i[1] = 1;
	while (n[i[0]] == 32 || (n[i[0]] >= 9 && n[i[0]] <= 13))
		i[0]++;
	if (n[i[0]] < '0' && n[i[0]] > '9' && n[i[0]] != '-' && n[i[0]] != '+')
		return (0);
	if (n[i[0]] == '-' || n[i[0]] == '+')
	{
		if (n[i[0]] == '-')
			i[1] = (i[1] * (-1));
		i[0]++;
	}
	while (('9' >= n[i[0]]) && (n[i[0]] >= '0'))
	{
		i[2] = (i[2] * 10) + (n[i[0]] - '0');
		i[0]++;
		if (i[2] * i[1] > 2147483647)
			return (-1);
		else if (i[2] * i[1] < -2147483648)
			return (0);
	}
	return (i[2] * i[1]);
}

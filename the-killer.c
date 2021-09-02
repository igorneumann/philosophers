/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the-killer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 18:41:12 by ineumann          #+#    #+#             */
/*   Updated: 2021/09/02 19:19:57 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	killer(t_data *philo, int *died)
{
	t_main	*main;
	int		i;

	i = 0;
	main = philo->main;
	while (died == 0 && philo->state != -1 && philo->tm_eat < main->tm_die)
		philo = philo->next;
	*died = 1;
	printf ("%llu, %i 🏴‍☠️ died\n", (get_time() - philo->main->tm_start),
		philo->number);
	while (++i <= main->ph_number)
	{
		philo->state = -1;
		philo = philo->next;
	}
}

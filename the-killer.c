/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the-killer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 18:41:12 by ineumann          #+#    #+#             */
/*   Updated: 2021/09/06 20:36:53 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	go_atomic(t_data *philo)
{
	t_main	*main;
	t_data	*temp;
	int		i;

	i = 0;
	main = philo->main;
	while (++i <= main->ph_number)
	{
		free(main->fork[i]);
		if (philo->next)
			temp = philo->next;
		free(philo);
		philo = temp;
	}
}

void	killer(t_data *philo, int *died)
{
	t_main	*main;
	int		i;

	i = 0;
	main = philo->main;
	while (*died != 1 && philo->state != -1 && (philo->tm_eat == 0
			|| philo->tm_eat < main->tm_die))
		if (philo->next)
			philo = philo->next;
	pthread_mutex_lock(philo->main->print);
	printf ("%llu, %i 🏴‍☠️ died\n", (get_time() - philo->main->tm_start),
		philo->number);
	close(1);
	pthread_mutex_unlock(philo->main->print);
	*died = 1;
	while (++i <= main->ph_number)
	{
		philo->state = -1;
		if (philo->next)
			philo = philo->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the-killer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 18:41:12 by ineumann          #+#    #+#             */
/*   Updated: 2021/09/08 18:48:37 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	go_atomic(t_data *philo)
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
	return (0);
}

void	killer(t_data *philo, int *died)
{
	t_main		*main;
	int			i;
	uint64_t	now;
	uint64_t	eaten;

	i = 0;
	now = 0;
	main = philo->main;
	while (*died != 1 && philo->state != -1
		&& (eaten <= main->tm_die))
	{
		main->tm_now = get_time();
		now = main->tm_now - main->tm_start;
		eaten = now - philo->tm_eat;
		if (philo->next)
			philo = philo->next;
	}
	pthread_mutex_lock(philo->main->print);
	printf ("main->tm_now es %llu\n", main->tm_now);
	printf ("philo->tm_eat is %llu\n", philo->tm_eat);
	printf ("now es %llu\n", now);
	printf ("eaten es %llu\n", eaten);
	printf ("time to die is %llu\n", main->tm_die);
	printf ("%llu, %i 🏴‍☠️ died\n", (main->tm_now - main->tm_start), philo->number);
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

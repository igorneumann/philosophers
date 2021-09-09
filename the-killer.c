/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the-killer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 18:41:12 by ineumann          #+#    #+#             */
/*   Updated: 2021/09/09 18:40:58 by ineumann         ###   ########.fr       */
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

void	killer_message(t_data *philo, int died)
{
	int	i;
	int	satisfied;

	i = 0;
	satisfied = 0;
	while (died < philo->main->ph_number)
	{
		if (philo->eaten >= philo->main->eatnum)
			satisfied++;
		usleep(10);
		if (philo->next)
			philo = philo->next;
		philo->state = -1;
		died++;
	}
	if (satisfied == philo->main->ph_number && philo->main->eatnum != 0)
	{
		printf ("%llu, 🍰🍔🍕 All philosophers had eaten enough!\n", (get_time()
				- philo->main->tm_start));
		printf ("%llu, 😊 They are fat and happy now...\n", (get_time()
				- philo->main->tm_start));
	}
	else
		printf ("%llu, philosopher %i 🏴‍☠️ died\n", (get_time()
				- philo->main->tm_start), philo->number);
}

void	killer(t_data *philo, int *died)
{
	t_main		*main;
	uint64_t	eaten;
	int			i;

	i = 0;
	main = philo->main;
	eaten = 0;
	while (*died != 1 && philo->state != -1 && eaten < main->tm_die)
	{
		eaten = (get_time() - main->tm_start - philo->tm_eat);
		if (philo->next)
			philo = philo->next;
	}
	pthread_mutex_lock(philo->main->print);
	if (eaten < main->tm_die)
		*died = 1;
	killer_message(philo, *died);
	close(1);
	pthread_mutex_unlock(philo->main->print);
	*died = 1;
}

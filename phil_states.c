/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil_states.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 19:06:38 by ineumann          #+#    #+#             */
/*   Updated: 2021/08/31 20:22:36 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	calc_time(t_data *philo, int type)
{
	if (type == 0)
		philo->tm_end = (get_time() - philo->main->tm_start)
			+ (philo->main->tm_sleep);
	else if (type == 1)
	{
		philo->tm_eat = get_time() - philo->main->tm_start;
		philo->tm_end = philo->tm_eat + (philo->main->tm_eat);
	}
}

void	evenoddlock(t_data *philo)
{
	if (philo->number % 2 == 0)
	{
		pthread_mutex_lock(philo->main->fork[philo->next->number]);
		printf("fork %i - ", philo->next->number);
		spitit("locked right fork", philo);
		pthread_mutex_lock(philo->main->fork[philo->number]);
		printf("fork %i - ", philo->number);
		spitit("locked left fork", philo);
	}
	else
	{
		pthread_mutex_lock(philo->main->fork[philo->number]);
		printf("fork %i - ", philo->number);
		spitit("locked left fork", philo);
		pthread_mutex_lock(philo->main->fork[philo->next->number]);
		printf("fork %i - ", philo->next->number);
		spitit("locked right fork", philo);
	}
}

int	phil_sleep(t_data *philo)
{
	calc_time (philo, 0);
	philo->state = 2;
	spitit("is sleeping", philo);
	rex_sit(philo);
	return (0);
}

int	phil_eat(t_data *philo)
{
	calc_time (philo, 1);
	evenoddlock(philo);
	philo->state = 1;
	philo->eaten += 1;
	spitit("is eating", philo);
	rex_sit(philo);
	pthread_mutex_unlock(philo->main->fork[philo->number]);
	printf("fork %i - ", philo->number);
	spitit("unlocked left fork", philo);
	pthread_mutex_unlock(philo->main->fork[philo->next->number]);
	printf("fork %i - ", philo->next->number);
	spitit("locked right fork", philo);
	return (0);
}

int	phil_think(t_data *philo)
{
	philo->state = 3;
	spitit("is thinking", philo);
	return (0);
}

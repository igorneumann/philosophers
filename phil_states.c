/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil_states.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 19:06:38 by ineumann          #+#    #+#             */
/*   Updated: 2021/08/30 20:48:15 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	phil_sleep(t_data *philo)
{
	philo->tm_end = (get_time() - philo->main->tm_start) + (philo->main->tm_sleep);
	philo->state = 2;
	pthread_mutex_lock(philo->main->print);
	printf ("%llu, %i is sleeping\n", (get_time() - philo->main->tm_start), philo->number);
	pthread_mutex_unlock(philo->main->print);
	while ((get_time() - philo->main->tm_start) < philo->tm_end)
		usleep(philo->main->ph_number * 10);
	return (0);
}

int	phil_eat(t_data *philo)
{
	philo->tm_eat = get_time() - philo->main->tm_start;
	philo->tm_end = philo->tm_eat + (philo->main->tm_eat);
	pthread_mutex_lock(philo->fork);
	pthread_mutex_lock(philo->prev->fork);
	philo->state = 1;
	philo->eaten += 1;
	pthread_mutex_lock(philo->main->print);
	printf ("%llu, %i is eating\n", philo->tm_eat, philo->number);
	pthread_mutex_unlock(philo->main->print);
	pthread_mutex_unlock(philo->fork);
	pthread_mutex_unlock(philo->prev->fork);
	while ((get_time() - philo->main->tm_start) < philo->tm_end)
		usleep(philo->main->ph_number * 10);
	return (0);
}

int	phil_think(t_data *philo)
{
	philo->state = 3;
	pthread_mutex_lock(philo->main->print);
	printf ("%llu, %i thinking\n", (get_time() - philo->main->tm_start), philo->number);
	pthread_mutex_unlock(philo->main->print);
	usleep(philo->main->ph_number * 10);
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil_states.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 19:06:38 by ineumann          #+#    #+#             */
/*   Updated: 2021/09/02 19:22:26 by ineumann         ###   ########.fr       */
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

void	lockit(t_data *philo, pthread_mutex_t **fork, int left, int right)
{
	int				ph;

	ph = philo->number;
	if ((ph % 2) == 0 && left && right)
	{
		pthread_mutex_lock(fork[right]);
		spitit("🍴 has taken the right fork", philo);
		pthread_mutex_lock(fork[left]);
		spitit("🍴 has taken the left fork", philo);
	}
	else
	{
		pthread_mutex_lock(fork[left]);
		spitit("🍴 has taken the left fork", philo);
		pthread_mutex_lock(fork[right]);
		spitit("🍴 has taken the right fork", philo);
	}
}

void	phil_eat(t_data *philo, int left, int right)
{
	pthread_mutex_t	**fork;

	if (philo->state != -1 && philo->main->died == 0)
	{
		fork = philo->main->fork;
		lockit(philo, fork, left, right);
		if (philo->state != -1 && philo->main->died == 0)
			philo->state = 1;
		spitit("🥩 is eating", philo);
		calc_time (philo, 1);
		philo->eaten += 1;
		rex_sit(philo);
		pthread_mutex_unlock(fork[left]);
		pthread_mutex_unlock(fork[right]);
		phil_sleep(philo, left, right);
	}
}

void	phil_sleep(t_data *philo, int left, int right)
{
	if (philo->state != -1 && philo->main->died == 0)
	{
		calc_time (philo, 0);
		if (philo->state != -1 && philo->main->died == 0)
			philo->state = 2;
		spitit("🙈 is sleeping", philo);
		rex_sit(philo);
		phil_think(philo, left, right);
	}
}

void	phil_think(t_data *philo, int left, int right)
{
	if (philo->state != -1 && philo->main->died == 0)
	{
		if (philo->state != -1 && philo->main->died == 0)
			philo->state = 3;
		spitit("🤯 is thinking", philo);
		phil_eat(philo, left, right);
	}
}

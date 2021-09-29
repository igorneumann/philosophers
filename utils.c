/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 20:06:06 by ineumann          #+#    #+#             */
/*   Updated: 2021/09/29 18:05:25 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	spitit(char *cad, t_data *philo)
{
	if (philo->state != -1 && philo->main->died == 0)
	{
		pthread_mutex_lock(philo->main->print);
		if (philo->state != -1 && philo->main->died == 0)
			printf ("%llu, %i %s\n", (get_time() - philo->main->tm_start),
				philo->number, cad);
		pthread_mutex_unlock(philo->main->print);
	}
}

void	rex_sit(t_data *philo)
{
	while (philo->state != -1 && philo->main->died == 0
		&& (get_time() - philo->main->tm_start) < philo->tm_end)
		usleep(philo->main->ph_number);
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

int	errors(int error)
{
	if (error == 1)
		printf("ERROR: Minimo 4 argumentos:\n");
	else if (error == 2)
		printf("ERROR: Maximo 5 argumentos:\n");
	if (error == 1 || error == 2)
	{
		printf("1 # filosofo\n2 tiempo para morrir\n3 tiempo para comer\n");
		printf("4 tiempo para dormir \nOpcional: # veces cada uno comera\n");
	}
	else if (error == 3)
		printf("ERROR: Minimo 1 filosofo\n");
	else if (error == 4)
		printf("ERROR: Los valores deben de estar entre 0 y 2147483647\n");
	return (-1);
}

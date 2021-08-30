/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 19:00:57 by ineumann          #+#    #+#             */
/*   Updated: 2021/08/30 20:49:32 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	return (-1);
}

t_data	*init(t_main *main, int argc, char **argv)
{
	int						i;
	t_data					*philo;
	static pthread_mutex_t	print;

	main->tm_start = get_time();
	main->ph_number = ft_atoi(argv[1]);
	main->tm_die = ft_atoi(argv[2]);
	main->tm_eat = ft_atoi(argv[3]);
	main->tm_sleep = ft_atoi(argv[4]);
	pthread_mutex_init(&print, NULL);
	main->print = &print;
	if (argc == 6)
		main->eatnum = ft_atoi(argv[5]);
	else
		main->eatnum = 0;
	i = main->ph_number + 1;
	while (--i > 0)
		ft_lst_add(&philo, ft_new(i, main->tm_start, main));
	return (philo);
}

void	*philo_routine(void *arg)
{
	t_data		*philo;

	philo = arg;
	while (philo->state != -1 && (philo->main->eatnum == 0
			|| philo->eaten < philo->main->eatnum))
	{
		if (philo->state == 1)
			phil_sleep(philo);
		else if (philo->state == 2)
			phil_think(philo);
		else
			phil_eat(philo);
	}
	return (NULL);
}

int	init_thread(t_data *philo)
{
	static pthread_mutex_t	fork;

	if (0 != pthread_create(&philo->thread, NULL, philo_routine, philo))
		return (-1);
	pthread_mutex_init(&fork, NULL);
	philo->fork = &fork;
	philo->tm_eat = get_time();
	pthread_join(philo->thread, NULL);
	return (0);
}

int	main(int argc, char **argv)
{
	t_main	main;
	t_data	*philo;
	int		i;

	i = 0;
	if (argc < 5)
		return (errors(1));
	else if (argc > 6)
		return (errors(2));
	philo = init(&main, argc, argv);
	while (++i <= main.ph_number)
	{
		if (init_thread(philo) != 0)
			return (-1);
		philo = philo->next;
	}
	return (0);
}
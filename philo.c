/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 19:00:57 by ineumann          #+#    #+#             */
/*   Updated: 2021/09/29 18:05:34 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	*init(t_main *main, int argc, char **argv, int *j)
{
	int						i;
	t_data					*philo;
	static pthread_mutex_t	print;

	philo = NULL;
	*j = 0;
	main->died = 0;
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
	main->fork = malloc((main->ph_number + 1) * sizeof(pthread_mutex_t *));
	while (--i > 0)
		ft_lst_add(&philo, ft_new(i, main->tm_start, main));
	return (philo);
}

void	*philo_routine(void *arg)
{
	t_data		*philo;
	int			left;
	int			right;

	philo = arg;
	left = philo->number;
	if (philo->next)
		right = philo->next->number;
	else
		right = -1;
	while (philo->state != -1 && (philo->main->eatnum == 0
			|| philo->eaten < philo->main->eatnum))
		phil_eat(philo, left, &right);
	return (NULL);
}

int	init_thread(t_data *philo, int ph_number)
{
	int	i;

	i = 0;
	while (++i <= ph_number)
	{
		if (0 != pthread_create(&philo->thread, NULL, philo_routine, philo))
			return (-1);
		philo->tm_eat = (get_time() - philo->main->tm_start);
		if (philo->next)
			philo = philo->next;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_main	main;
	t_data	*philo;
	int		i;

	if (argc < 5)
		return (errors(1));
	else if (argc > 6)
		return (errors(2));
	philo = init(&main, argc, argv, &i);
	if (main.ph_number < 1)
		return (errors(3));
	if (main.tm_die < 1 || main.tm_eat < 1
		|| main.tm_sleep < 1 || main.eatnum < 0)
		return (errors(4));
	return (do_magic(main, philo, i));
}

int	do_magic(t_main main, t_data *philo, int i)
{
	while (++i <= main.ph_number)
	{
		main.fork[i] = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(main.fork[i], NULL);
	}
	if (init_thread(philo, main.ph_number) != 0)
		return (-1);
	killer(philo, &main.died);
	while (--i > 0 && main.died != 1 && philo->state != -1)
	{
		pthread_join(philo->thread, NULL);
		if (philo->next)
			philo = philo->next;
	}
	return (go_atomic(philo));
}

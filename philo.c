/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 19:00:57 by ineumann          #+#    #+#             */
/*   Updated: 2021/08/26 20:17:03 by ineumann         ###   ########.fr       */
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

int	init(t_main *main, int argc, char **argv)
{
	int	i;

	main->ph_number = ft_atoi(argv[1]);
	main->tm_die = ft_atoi(argv[2]);
	main->tm_eat = ft_atoi(argv[3]);
	main->tm_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		main->eatnum = ft_atoi(argv[5]);
	i = main->ph_number + 1;
	while (--i > 0)
		ft_lst_add(&main->phil, ft_new(i));
	return (0);
}

void	*philo_routine(void *arg)
{
	t_main		*main;
	uint64_t	time;
	int			state;

	main = arg;
	while (main->phil->state != -1)
	{
		time = main->phil->tm_state;
		if (main->phil->state == 1 && (get_time() - time) >= main->tm_die)
			main->phil->state = -1;
		if (check_death(main->phil))
			break ;
		if (main->phil->state == 0 || main->phil->state == 3)
			state = phil_eat(main);
		else if (main->phil->state == 1 && (get_time() - time) >= main->tm_eat)
			state = phil_sleep(main);
		else if (main->phil->state == 2
			&& (get_time() - time) >= main->tm_sleep)
			state = phil_think(main);
	}
	return (NULL);
}

int	init_thread(t_main	*main)
{
	if (0 != pthread_create(&main->phil->thread, NULL, philo_routine, main))
		return (-1);
	pthread_join(main->phil->thread, NULL);
	return (0);
}

int	main(int argc, char **argv)
{
	t_main	main;
	int		i;

	i = 0;
	if (argc < 5)
		return (errors(1));
	else if (argc > 6)
		return (errors(2));
	init(&main, argc, argv);
	while (++i <= main.ph_number)
	{
		if (init_thread(&main) != 0)
			return (-1);
		main.phil = main.phil->next;
	}
	return (0);
}
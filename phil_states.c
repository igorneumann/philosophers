/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil_states.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 19:06:38 by ineumann          #+#    #+#             */
/*   Updated: 2021/08/26 20:10:54 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	phil_sleep(t_main *main)
{
	printf ("%llu, %i is sleeping\n", get_time(), main->phil->number);
	return (0);
}

int	phil_eat(t_main *main)
{
	if (main->phil->state != 1 && main->phil->fork == 1
		&& main->phil->prev->fork == 1)
	{
		main->phil->fork = 0;
		main->phil->prev->fork = 0;
		main->phil->tm_state = get_time();
		main->phil->state = 1;
		printf ("%llu, %i is eating\n", get_time(), main->phil->number);
		return (1);
	}
	return (0);
}

int	phil_think(t_main *main)
{
	printf ("%llu, %i thinking\n", get_time(), main->phil->number);
	return (0);
}
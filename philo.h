/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 18:56:56 by ineumann          #+#    #+#             */
/*   Updated: 2021/08/26 20:10:54 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <fcntl.h>
# include <stddef.h>

typedef struct s_data
{
	struct s_data	*prev;
	pthread_t		thread;
	int				number; // # del filosofo
	int				fork; // tenedor a su redecha disponible
	int				state; // estado -1 dead, 0 (idle - initial state), 1 (eating), 2 (sleeping), 3 (thinking)
	uint64_t		tm_state; // hora de ultimo estado
	int				eaten; // numero de veces que ha comido
	struct s_data	*next;
}					t_data;

typedef struct s_main
{
	int			ph_number; // numero de filosofos
	uint64_t	tm_die; // tiempo para morrirse
	uint64_t	tm_eat; // tiempo para comer
	uint64_t	tm_sleep; // tiempo para dormir
	int			eatnum; // cuantas veces tienen que comer
	t_data		*phil; // tabla primer filosofo
}			t_main;

/*
*** philo.c
*/

int			errors(int error);
int			init(t_main *main, int argc, char **argv);
int			init_thread(t_main	*main);
int			main (int argc, char **argv);

/*
*** utils.c
*/

int			check_death(t_data *elem);
uint64_t	get_time(void);
int			ft_atoi(const char *n);

/*
*** lists.c
*/

t_data		*ft_new(int ph_number);
void		ft_lst_add(t_data **in, t_data *new);
void		ft_lst_edit(t_data **in, t_data *new);

/*
*** lists_utils.c
*/

t_data		*ft_lst_last(t_data *elem);
t_data		*ft_lst_first(t_data *elem);
t_data		*remove_elem(t_data *elem);

/*
*** phil_states.c
*/

int			phil_sleep(t_main *main);
int			phil_eat(t_main *main);
int			phil_think(t_main *main);

#endif
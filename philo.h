/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 18:56:56 by ineumann          #+#    #+#             */
/*   Updated: 2021/09/29 18:04:56 by ineumann         ###   ########.fr       */
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

typedef struct s_main
{
	int				ph_number;
	int				died;
	uint64_t		tm_start;
	uint64_t		tm_die;
	uint64_t		tm_eat;
	uint64_t		tm_sleep;
	pthread_mutex_t	**fork;
	pthread_mutex_t	*print;
	int				eatnum;
}			t_main;

typedef struct s_data
{
	struct s_data	*prev;
	struct s_data	*next;
	t_main			*main;
	pthread_t		thread;
	int				number;
	int				state;
	uint64_t		tm_eat;
	uint64_t		tm_end;
	int				eaten;
}					t_data;

/*
*** philo.c
*/

t_data		*init(t_main *main, int argc, char **argv, int *i);
void		*philo_routine(void *arg);
int			init_thread(t_data *philo, int ph_number);
int			main(int argc, char **argv);
int			do_magic(t_main main, t_data *philo, int i);

/*
*** utils.c
*/

void		spitit(char *cad, t_data *philo);
void		rex_sit(t_data *philo);
uint64_t	get_time(void);
int			ft_atoi(const char *n);
int			errors(int error);

/*
*** lists.c
*/

t_data		*ft_new(int ph_number, uint64_t tm_start, t_main *main);
void		ft_lst_add(t_data **in, t_data *new);

/*
*** lists_utils.c
*/

t_data		*ft_lst_last(t_data *elem);
t_data		*ft_lst_first(t_data *elem);
t_data		*remove_elem(t_data *elem);

/*
*** phil_states.c
*/

void		evenoddunlock(t_data *philo);
void		lockit(t_data *philo, pthread_mutex_t **fork, int left, int *right);
void		calc_time(t_data *philo, int type);
void		phil_sleep(t_data *philo, int left, int right);
void		phil_eat(t_data *philo, int left, int *right);
void		phil_think(t_data *philo, int left, int right);

/*
*** the-killer.c
*/

int			go_atomic(t_data *philo);
void		killer(t_data *philo, int *died);
void		killer_message(t_data *philo, int died);

#endif
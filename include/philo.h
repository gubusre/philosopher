/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubusque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 15:37:40 by gubusque          #+#    #+#             */
/*   Updated: 2026/02/09 21:53:00 by gubusque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include "libft.h"

typedef struct s_data t_data;

typedef struct s_philo
{
	pthread_t thread;
	int	id;
	t_data	*data;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	time_t	last_meal_time;
	int	meals_eaten;
	int	is_eating;
} t_philo;

struct s_data
{
	int				n_philo;
	long long		t_die;
	long long		t_eat;
	long long		t_sleep;
	int				nt_eat;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	full_mutex;
	int				simulation_stop;
	int				philos_full;
};

/* Prototipos de Funciones */

// Checkers & Init
int			check_valid_input(int argc, char **argv);
int			init_data(int argc, char **argv, t_data *data);
int			check_if_all_full(t_data *data, t_philo *philo);
int			check_if_dead(t_philo *philo);
t_philo		*init_philos(t_data *data);

// Threads & Routine
int			create_threads(t_data *data, t_philo *philos);
void		*philo_routine(void *arg);
void		join_threads(t_data *data, t_philo *philos);

// Acciones
void		philo_eat(t_philo *philo);
void		philo_sleep(t_philo *philo);
void		philo_think(t_philo *philo);
void		print_status(char *str, t_philo *philo);

// Monitor / Supervisor
void		supervisor(t_data *data, t_philo *philos);
int			check_if_dead(t_philo *philo);
int			get_simulation_status(t_data *data);
void		stop_simulation(t_data *data);
void		print_death_message(t_philo *philo);

// Utils & Time
long long	get_current_time(void);
void		precise_usleep(long long time_in_ms, t_data *data);
void		clean_data(t_data *data, t_philo *philos);

#endif

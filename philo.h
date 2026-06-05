/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubusque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 22:59:48 by gubusque          #+#    #+#             */
/*   Updated: 2026/06/05 22:59:50 by gubusque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long long		last_meal;
	pthread_t		thread;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
	pthread_mutex_t	meal_mutex;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	int				n_philo;
	long long		t_die;
	long long		t_eat;
	long long		t_sleep;
	int				must_eat;
	int				stop;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	state_mutex;
	t_philo			*philos;
}	t_data;

int			parse_args(t_data *data, int argc, char **argv);
int			init_data(t_data *data);
void		cleanup(t_data *data);
long long	get_time(void);
void		precise_sleep(long long ms, t_data *data);
int			sim_stopped(t_data *data);
void		set_stop(t_data *data);
void		print_status(t_philo *p, const char *msg);
void		*routine(void *arg);
void		*monitor(void *arg);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubusque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 15:37:40 by gubusque          #+#    #+#             */
/*   Updated: 2026/02/04 17:40:20 by gubusque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


typedef struct s_data
{
	int	n_philo;
	time_t	t_die;
	time_t	t_eat;
	time_t	t_sleep;
	int	nt_eat;
	
	time_t	start_time;
	
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	full_mutex;
	
	int	simulation_stop;
	int	philos_full;
} t_data;

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

void	check_valid_input(int argc, char *argv[]);

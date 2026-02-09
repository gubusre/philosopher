/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubusque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 16:34:37 by gubusque          #+#    #+#             */
/*   Updated: 2026/02/09 22:02:39 by gubusque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_if_all_full(t_data *data, t_philo *philos)
{
	int	i;
	int	full;

	i = 0;
	full = 0;
	while (i < data->n_philo)
	{
		pthread_mutex_lock(&data->dead_mutex);
		if (philos[i].meals_eaten >= data->nt_eat)
			full++;
		pthread_mutex_unlock(&data->dead_mutex);
		i++;
	}
	if (full == data->n_philo)
		return (1);
	return (0);
}

int	check_if_dead(t_philo *philo)
{
	long long	current;
	long long	last_meal;

	pthread_mutex_lock(&philo->data->dead_mutex);
	current = get_current_time();
	last_meal = philo->last_meal_time;
	if (current - last_meal >= philo->data->t_die)
	{
		pthread_mutex_unlock(&philo->data->dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->dead_mutex);
	return (0);
}

int	check_valid_input(int argc, char *argv[])
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		if (!argv[i][j])
			return (1);
		while (argv[i][j])
		{
			if (argv[i][j] < 48 || argv[i][j] > 57)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

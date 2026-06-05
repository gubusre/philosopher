/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubusque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 22:59:09 by gubusque          #+#    #+#             */
/*   Updated: 2026/06/05 22:59:11 by gubusque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_forks(t_data *data, int i)
{
	int	right;

	right = (i + 1) % data->n_philo;
	if (i % 2 == 0)
	{
		data->philos[i].first_fork = &data->forks[i];
		data->philos[i].second_fork = &data->forks[right];
	}
	else
	{
		data->philos[i].first_fork = &data->forks[right];
		data->philos[i].second_fork = &data->forks[i];
	}
}

static int	init_one(t_data *data, int i)
{
	data->philos[i].id = i;
	data->philos[i].meals_eaten = 0;
	data->philos[i].last_meal = 0;
	data->philos[i].data = data;
	assign_forks(data, i);
	if (pthread_mutex_init(&data->philos[i].meal_mutex, NULL) != 0)
		return (1);
	return (0);
}

static int	init_philos(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->n_philo);
	if (!data->philos)
		return (1);
	i = 0;
	while (i < data->n_philo)
	{
		if (init_one(data, i) != 0)
			return (1);
		i++;
	}
	return (0);
}

static int	init_forks(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philo);
	if (!data->forks)
		return (1);
	i = 0;
	while (i < data->n_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	init_data(t_data *data)
{
	data->stop = 0;
	data->forks = NULL;
	data->philos = NULL;
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->state_mutex, NULL) != 0)
		return (1);
	if (init_forks(data) != 0)
		return (1);
	if (init_philos(data) != 0)
		return (1);
	return (0);
}

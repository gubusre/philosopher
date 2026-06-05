/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubusque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 22:59:59 by gubusque          #+#    #+#             */
/*   Updated: 2026/06/05 23:00:00 by gubusque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long long)tv.tv_sec * 1000 + (long long)tv.tv_usec / 1000);
}

int	sim_stopped(t_data *data)
{
	int	stopped;

	pthread_mutex_lock(&data->state_mutex);
	stopped = data->stop;
	pthread_mutex_unlock(&data->state_mutex);
	return (stopped);
}

void	set_stop(t_data *data)
{
	pthread_mutex_lock(&data->state_mutex);
	data->stop = 1;
	pthread_mutex_unlock(&data->state_mutex);
}

void	precise_sleep(long long ms, t_data *data)
{
	long long	start;

	start = get_time();
	while (get_time() - start < ms)
	{
		if (sim_stopped(data))
			break ;
		usleep(200);
	}
}

void	cleanup(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		if (data->philos)
			pthread_mutex_destroy(&data->philos[i].meal_mutex);
		if (data->forks)
			pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->state_mutex);
	free(data->philos);
	free(data->forks);
}

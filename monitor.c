/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubusque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 22:59:22 by gubusque          #+#    #+#             */
/*   Updated: 2026/06/05 22:59:23 by gubusque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_died(t_philo *p)
{
	long long	last;

	pthread_mutex_lock(&p->meal_mutex);
	last = p->last_meal;
	pthread_mutex_unlock(&p->meal_mutex);
	if (get_time() - last > p->data->t_die)
		return (1);
	return (0);
}

static void	announce_death(t_philo *p)
{
	pthread_mutex_lock(&p->data->print_mutex);
	pthread_mutex_lock(&p->data->state_mutex);
	p->data->stop = 1;
	pthread_mutex_unlock(&p->data->state_mutex);
	printf("%lld %d died\n", get_time() - p->data->start_time, p->id + 1);
	pthread_mutex_unlock(&p->data->print_mutex);
}

static int	all_full(t_data *data)
{
	int	i;
	int	full;

	if (data->must_eat < 0)
		return (0);
	i = 0;
	full = 1;
	while (i < data->n_philo)
	{
		pthread_mutex_lock(&data->philos[i].meal_mutex);
		if (data->philos[i].meals_eaten < data->must_eat)
			full = 0;
		pthread_mutex_unlock(&data->philos[i].meal_mutex);
		i++;
	}
	return (full);
}

void	*monitor(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (!sim_stopped(data))
	{
		i = 0;
		while (i < data->n_philo)
		{
			if (philo_died(&data->philos[i]))
			{
				announce_death(&data->philos[i]);
				return (NULL);
			}
			i++;
		}
		if (all_full(data))
		{
			set_stop(data);
			return (NULL);
		}
		usleep(100);
	}
	return (NULL);
}

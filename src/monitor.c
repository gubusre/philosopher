/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubusque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 20:21:29 by gubusque          #+#    #+#             */
/*   Updated: 2026/02/09 21:51:00 by gubusque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_death_message(t_philo *philo)
{
	long long	time;

	pthread_mutex_lock(&philo->data->write_mutex);
	time = get_current_time() - philo->data->start_time;
	printf("%lld %d died\n", time, philo->id);
	pthread_mutex_unlock(&philo->data->write_mutex);
}

int	get_simulation_status(t_data *data)
{
	int	res;

	pthread_mutex_lock(&data->dead_mutex);
	res = data->simulation_stop;
	pthread_mutex_unlock(&data->dead_mutex);
	return (res);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubusque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 20:28:37 by gubusque          #+#    #+#             */
/*   Updated: 2026/02/09 21:59:18 by gubusque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	stop_simulation(t_data *data)
{
	pthread_mutex_lock(&data->dead_mutex);
	data->simulation_stop = 1;
	pthread_mutex_unlock(&data->dead_mutex);
}

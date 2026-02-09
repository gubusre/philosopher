/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubusque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 20:33:34 by gubusque          #+#    #+#             */
/*   Updated: 2026/02/09 21:54:35 by gubusque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	join_threads(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		if (pthread_join(philos[i].thread, NULL) != 0)
			return ;
		i++;
	}
}

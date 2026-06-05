/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubusque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 22:59:04 by gubusque          #+#    #+#             */
/*   Updated: 2026/06/05 22:59:06 by gubusque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_philo *p, const char *msg)
{
	long long	t;

	pthread_mutex_lock(&p->data->print_mutex);
	if (!sim_stopped(p->data))
	{
		t = get_time() - p->data->start_time;
		printf("%lld %d %s\n", t, p->id + 1, msg);
	}
	pthread_mutex_unlock(&p->data->print_mutex);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubusque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 22:59:53 by gubusque          #+#    #+#             */
/*   Updated: 2026/06/05 22:59:54 by gubusque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eat(t_philo *p)
{
	pthread_mutex_lock(p->first_fork);
	print_status(p, "has taken a fork");
	pthread_mutex_lock(p->second_fork);
	print_status(p, "has taken a fork");
	pthread_mutex_lock(&p->meal_mutex);
	p->last_meal = get_time();
	pthread_mutex_unlock(&p->meal_mutex);
	print_status(p, "is eating");
	precise_sleep(p->data->t_eat, p->data);
	pthread_mutex_lock(&p->meal_mutex);
	p->meals_eaten++;
	pthread_mutex_unlock(&p->meal_mutex);
	pthread_mutex_unlock(p->first_fork);
	pthread_mutex_unlock(p->second_fork);
}

static void	think(t_philo *p)
{
	long long	t;

	print_status(p, "is thinking");
	if (p->data->n_philo % 2 == 0)
		return ;
	t = p->data->t_die - p->data->t_eat - p->data->t_sleep;
	if (t < 0)
		t = 0;
	precise_sleep(t / 2, p->data);
}

static void	*lone_philo(t_philo *p)
{
	pthread_mutex_lock(p->first_fork);
	print_status(p, "has taken a fork");
	while (!sim_stopped(p->data))
		usleep(200);
	pthread_mutex_unlock(p->first_fork);
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	if (p->data->n_philo == 1)
		return (lone_philo(p));
	if (p->id % 2 == 0)
		precise_sleep(p->data->t_eat / 2, p->data);
	while (!sim_stopped(p->data))
	{
		eat(p);
		print_status(p, "is sleeping");
		precise_sleep(p->data->t_sleep, p->data);
		think(p);
	}
	return (NULL);
}

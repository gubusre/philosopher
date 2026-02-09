/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubusque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 19:00:37 by gubusque          #+#    #+#             */
/*   Updated: 2026/02/09 22:11:55 by gubusque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(char *str, t_philo *philo)
{
	long long	time;

	pthread_mutex_lock(&philo->data->write_mutex);
	time = get_current_time() - philo->data->start_time;
	if (!get_simulation_status(philo->data))
	{
		/* printf*/
		printf("%lld %d %s\n", time, philo->id, str);
	}
}

void	p_sleep(t_philo *philo)
{
	print_status("is sleeping", philo);
	precise_usleep(philo->data->t_sleep, philo->data);
}

void	p_think(t_philo *philo)
{
	print_status("is thinking", philo);
	/*en casos donde el time to die es muy corto se podria poner un usleep*/
}

void	p_eat(t_philo *philo)
{
	if (get_simulation_status(philo->data))
		return ;
	pthread_mutex_lock(philo->left_fork);
	print_status("has taken a fork", philo);
	if (philo->data->n_philo == 1)
	{
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	pthread_mutex_lock(philo->right_fork);
	print_status("has taken a fork", philo);
	print_status("is eating", philo);
	pthread_mutex_lock(&philo->data->dead_mutex);
	philo->last_meal_time = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->dead_mutex);
	precise_usleep(philo->data->t_eat, philo->data);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void precise_usleep(long long time_in_ms, t_data *data)
{
	long long	start_time;

	start_time = get_current_time();
	while ((get_current_time() - start_time) < time_in_ms)
	{
		if (get_simulation_status(data))
				break ;
		usleep(500);
	}
}

void	*philo_routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if (philo->data->n_philo == 1)
	{
		print_status("has taken a fork", philo);
		precise_usleep(philo->data->t_die, philo->data);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		precise_usleep(philo->data->t_eat / 2, philo->data);
	while (get_simulation_status(philo->data) == 0)
	{
		p_eat(philo);
		p_sleep(philo);
		p_think(philo);
		usleep(100);
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubusque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 22:59:14 by gubusque          #+#    #+#             */
/*   Updated: 2026/06/05 22:59:15 by gubusque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	join_philos(t_data *data, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}

static void	set_start(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_time();
	while (i < data->n_philo)
	{
		data->philos[i].last_meal = data->start_time;
		i++;
	}
}

static int	create_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		if (pthread_create(&data->philos[i].thread, NULL, routine,
				&data->philos[i]) != 0)
		{
			set_stop(data);
			join_philos(data, i);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	start_sim(t_data *data, pthread_t *mon)
{
	set_start(data);
	if (create_philos(data) != 0)
		return (1);
	if (pthread_create(mon, NULL, monitor, data) != 0)
	{
		set_stop(data);
		join_philos(data, data->n_philo);
		return (1);
	}
	join_philos(data, data->n_philo);
	pthread_join(*mon, NULL);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data		data;
	pthread_t	mon;

	if (argc != 5 && argc != 6)
	{
		printf("Usage: ./philo n_philo t_die t_eat t_sleep [must_eat]\n");
		return (1);
	}
	if (parse_args(&data, argc, argv) != 0)
	{
		printf("Error: invalid arguments\n");
		return (1);
	}
	if (init_data(&data) != 0)
	{
		printf("Error: initialization failed\n");
		return (1);
	}
	start_sim(&data, &mon);
	cleanup(&data);
	return (0);
}

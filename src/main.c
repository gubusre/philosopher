/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubusque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 15:36:51 by gubusque          #+#    #+#             */
/*   Updated: 2026/02/09 22:04:55 by gubusque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	supervisor(t_data *data, t_philo *philos)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < data->n_philo)
		{
			if (check_if_dead(&philos[i]))
			{
				stop_simulation(data);
				print_death_message(&philos[i]);
				return ;
			}
			i++;
		}
		if (data->nt_eat != -1 && check_if_all_full(data, philos))
		{
			stop_simulation(data);
			return ;
		}
		usleep(1000);
	}

}

int	create_threads(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		if (pthread_create(&philos[i].thread, NULL, &philo_routine, &philos[i]) != 0)
			return (1);
		pthread_mutex_lock(&data->dead_mutex);
		philos[i].last_meal_time = data->start_time;
		pthread_mutex_unlock(&data->dead_mutex);
		i++;
	}
	return (0);
}

t_philo	*init_philos(t_data *data)
{
	t_philo *philos;
	int	i;

	philos = malloc(sizeof(t_philo) * data->n_philo);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < data->n_philo)
	{
		philos[i].id = i + 1;
		philos[i].data = data;
		philos[i].meals_eaten = 0;
		philos[i].is_eating = 0;
		philos[i].last_meal_time = 0;
		philos[i].left_fork = &data->forks[i];
		philos[i].right_fork = &data->forks[(i + 1) % data->n_philo];
		i++;
	}
	return (philos);
}

int	init_data(int argc, char *argv[], t_data *data)
{
	int	i;

	data->n_philo = ft_atoi(argv[1]);
	data->t_die = ft_atoi(argv[2]);
	data->t_eat = ft_atoi(argv[3]);
	data->t_sleep = ft_atoi(argv[4]);
	data->nt_eat = -1;
	if (argc == 6)
		data->nt_eat = ft_atoi(argv[5]);
	data->simulation_stop = 0;
	data->philos_full = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philo);
	if(!data->forks)
		return (1);
	i = 0;
	while (i < data->n_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	if (pthread_mutex_init(&data->write_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->dead_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->full_mutex, NULL) != 0)
		return (1);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data	data;
	t_philo	*philos;

	if (argc < 5 || argc > 6)
		return (1);
	if (check_valid_input(argc, argv) != 0)
		return (1);
	if (init_data(argc, argv, &data) != 0)
		return (1);
	philos = init_philos(&data);
	if (!philos)
		return (clean_data(&data, NULL), 1);
	data.start_time = get_current_time();
	if (create_threads(&data, philos) != 0)
		return(clean_data(&data, philos), 1);
	supervisor(&data, philos);
	join_threads(&data, philos);
	clean_data(&data, philos);
	return (0);
}

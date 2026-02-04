/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubusque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 15:36:51 by gubusque          #+#    #+#             */
/*   Updated: 2026/02/04 17:14:31 by gubusque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(int argc, char *argv[], void input)
{
	input.n_philo = ft_atoi(argv[1]);
	input.t_die = ft_atoi(argv[2]);
	input.t_eat = ft_atoi(argv[3]);
	input.t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		input.nt_eat = ft_atoi(argv[5]);
	else
		input.nt_eat = -1;
}

int	main(int argc, char *argv[])
{
	t_data	data;
	t_philo	*philos;

	if (argc != 5 || argc != 6)
		return (1);
	else
		check_valid_input(argc, argv);
	if (init_data(argc, argv, &data) != 0)
		return (1);
	philos = init_philos(&data);
	if (!philos)
	{
		clean_data(&data);
		return (1);
	}
	data.start_time = get_current_time();
	if (create_threads(philos, %data) != 0)
	{
		clean_data(&data, philos);
		return (1);
	}
	supervisor(&data, philos); /*gestiona loop para crear threads*/
	join_threads(philos, data.n_philo);
	clean_data(&data, philos);
	return (0);
}

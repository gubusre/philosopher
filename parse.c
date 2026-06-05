/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubusque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 22:59:30 by gubusque          #+#    #+#             */
/*   Updated: 2026/06/05 22:59:32 by gubusque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_digits(const char *s)
{
	int	i;

	i = 0;
	if (!s || !s[0])
		return (0);
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static long long	ft_atol(const char *s)
{
	long long	n;
	int			i;

	n = 0;
	i = 0;
	while (s[i] >= '0' && s[i] <= '9')
	{
		n = n * 10 + (s[i] - '0');
		i++;
	}
	return (n);
}

static int	check_values(t_data *data)
{
	if (data->t_die < 1 || data->t_eat < 1 || data->t_sleep < 1)
		return (1);
	if (data->must_eat == 0)
		return (1);
	return (0);
}

int	parse_args(t_data *data, int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!is_digits(argv[i]))
			return (1);
		i++;
	}
	data->n_philo = (int)ft_atol(argv[1]);
	data->t_die = ft_atol(argv[2]);
	data->t_eat = ft_atol(argv[3]);
	data->t_sleep = ft_atol(argv[4]);
	data->must_eat = -1;
	if (argc == 6)
		data->must_eat = (int)ft_atol(argv[5]);
	return (check_values(data));
}

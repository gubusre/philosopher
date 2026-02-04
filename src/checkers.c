/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubusque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 16:34:37 by gubusque          #+#    #+#             */
/*   Updated: 2026/02/04 16:39:20 by gubusque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	check_valid_input(int argc, char *argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (i <= argc)
	{
		while (argv[j])
		{
			if (argv[i][j] < 48 && argv[i][j] > 57)
				exit(0);
			j++:
		}
		i++;
	}
}

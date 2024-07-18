/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoeno <ssoeno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:06:29 by ssoeno            #+#    #+#             */
/*   Updated: 2024/07/18 17:51:44 by ssoeno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	clean(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		pthread_mutex_destroy(&table->forks[i].fork);
		i++;
	}
	pthread_mutex_destroy(&table->table_mutex);
	free(table->forks);
	free(table->philos);
}

int	main(int ac, char **av)
{
	t_table	table;

	if (ac == 5 || ac == 6)
	{
		parse_input(&table, av);
		data_init(&table);
		dinner_start(&table);
		clean(&table);
	} else
	{
		error_exit("Input example: ./philo 5 800 200 200");
	}
	return (0);
}
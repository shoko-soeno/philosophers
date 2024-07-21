/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoeno <ssoeno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:06:29 by ssoeno            #+#    #+#             */
/*   Updated: 2024/07/21 16:18:51 by ssoeno           ###   ########.fr       */
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
		//debug
		printf("before data init***********philo_nbr: %ld\n", table.philo_nbr);
		data_init(&table);
		//debug
		printf("before dinner start***************philo_nbr: %ld\n", table.philo_nbr);
		dinner_start(&table);
		//debug
		printf("before clean****************philo_nbr: %ld\n", table.philo_nbr);
		clean(&table);
	} else
	{
		error_exit("Input example: ./philo 5 800 200 200");
	}
	return (0);
}

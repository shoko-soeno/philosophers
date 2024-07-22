/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoeno <ssoeno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:15:00 by ssoeno            #+#    #+#             */
/*   Updated: 2024/07/21 14:51:58 by ssoeno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	assign_forks(t_philo *philo, t_fork *forks, int philo_position)
{
	int philo_nbr;
	
	philo_nbr = philo->table->philo_nbr;
	// printf("assign_forks***************************\n"); //debug
	// printf("philo_position: %d\n", philo_position); //debug
	// printf("philo_id: %d\n", philo->id);
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[philo_position];
		philo->second_fork = &forks[(philo_position + 1) % philo_nbr];
	}
	else
	{
		philo->first_fork = &forks[(philo_position + 1) % philo_nbr];
		philo->second_fork = &forks[philo_position];
	}
	// printf("philo_first_fork: %p\n", philo->first_fork);
	// printf("philo_second_fork: %p\n", philo->second_fork);
	// printf("philo_philo_position: %d\n", philo_position);
	// printf("philo_philo_table: %p\n", philo->table);
}

static void		philo_init(t_table *table)
{
	int	i;
	t_philo	*philo;

	i = -1;
	while (++i < table->philo_nbr)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->full = false;
		philo->meals_counter = 0;
		philo->table = table;
		safe_mutex_handle(&philo->philo_mutex, INIT);
		assign_forks(philo, table->forks, i);
		// //debug
		// printf("philo init*************************\n");
		// printf("philo_id: %d\n", philo->id);
		// printf("philo_meals_counter: %ld\n", philo->meals_counter);
		// // printf("philo_table: %p\n", philo->table);
		// printf("philo_first_fork: %p\n", philo->first_fork);
		// printf("philo_second_fork: %p\n", philo->second_fork);
		// printf("philo_philo_mutex: %p\n", &philo->philo_mutex);
	}
	printf("philo init finished*************************\n");
}

void	data_init(t_table *table)
{
	int i;

	i = -1;
	table->end_simulation = false;
	table->all_threads_ready = false;
	table->philos = safe_malloc(sizeof(t_philo) * table->philo_nbr);
	safe_mutex_handle(&table->table_mutex, INIT);
	table->forks = safe_malloc(sizeof(t_fork) * table->philo_nbr);
	// printf("data init*****************************\n"); //debug
	while (++i < table->philo_nbr)
	{
		safe_mutex_handle(&table->forks[i].fork, INIT);
		table->forks[i].fork_id = i;
		//debug
		// printf("fork_id: %d\n", table->forks[i].fork_id);
	}
	philo_init(table);
}

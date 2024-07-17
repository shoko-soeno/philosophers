/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoeno <ssoeno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:47:16 by ssoeno            #+#    #+#             */
/*   Updated: 2024/07/17 18:40:12 by ssoeno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

static void	eat(t_philo *philo)
{
	safe_mutex_handle(&philo->first_fork->fork, LOCK);
	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	safe_mutex_handle(&philo->second_fork->fork, LOCK);
	write_status(TAKE_SECOND_FORK, philo, DEBUG_MODE);
	
	set_long(&philo->philo_mutex, gettime(MILLISECOND));
	philo->meals_counter++;
	write_status(EATING, philo, DEBUG_MODE);
	precise_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->nbr_limit_meals > 0
		&& philo->meals_counter == philo->table->nbr_limit_meals)
		set_bool(&philo->philo_mutex, &philo->full, true);
	safe_mutex_handle(&philo->first_fork->fork, UNLOCK);
	safe_mutex_handle(&philo->second_fork->fork, UNLOCK);
}

void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;

	waite_all_threads_ready(philo->table); //spinlock
	
	//set last meal time
	
	while (!simulation_finished(philo->table))
	{
		if(philo->full)
			break ;
		//eat
		eat(philo);
		//sleep (write status and precise usleep)
		write_status(SLEEPING, philo, DEBUG_MODE);
		precise_usleep(philo->table->time_to_sleep, philo->table);
		//think
		thinking(philo);
		write_status(THINKING, philo, DEBUG_MODE);
	}
	return (NULL);

}

void	dinner_start(t_table *table)
{
	int	i;
	
	i = -1;
	if (table->nbr_limit_meals)
		return ;
	else if (table->nbr_limit_meals == 1)
	{
		return ;
	}
	else
	{
		while (++i < table->philo_nbr)
		{
			safe_thread_handle(&table->philos[i].thread_id, 
				dinner_simulation, &table->philos[i], CREATE);
		}
	}

	//start of simulaion
	table->start_simulation = gettime(MILLISECOND);
	//all threads are ready!
	set_bool(&table->table_mutex, &table->all_threads_ready, true);
	//wait for all threads to finish
	i = -1;
	while (++i < table->philo_nbr)
	{
		safe_thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN);
	}
	//all threads finished
	
}
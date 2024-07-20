/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoeno <ssoeno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:47:16 by ssoeno            #+#    #+#             */
/*   Updated: 2024/07/20 16:38:30 by ssoeno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	thinking(t_philo *philo)
{
	write_status(THINKING, philo, DEBUG_MODE);
}

/* eat routine
1. grab the forks : here first & second fork is handy
2. eat : write eat, update last meal, update meals counter
3. release the forks
*/
static void	eat(t_philo *philo)
{
	printf("eat function: philo %d is eating\n", philo->id); //debug
	safe_mutex_handle(&philo->first_fork->fork, LOCK);
	printf("philo %d took first fork\n", philo->id); //debug
	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	safe_mutex_handle(&philo->second_fork->fork, LOCK);
	write_status(TAKE_SECOND_FORK, philo, DEBUG_MODE);
	
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
	philo->meals_counter++;
	printf("philo %d meals_counter: %ld\n", philo->id, philo->meals_counter); //debug
	write_status(EATING, philo, DEBUG_MODE);
	precise_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->nbr_limit_meals > 0
		&& philo->meals_counter == philo->table->nbr_limit_meals)
	{
		set_bool(&philo->philo_mutex, &philo->full, true);
		printf("philo %d is full\n", philo->id); //debug
	}
	safe_mutex_handle(&philo->first_fork->fork, UNLOCK);
	safe_mutex_handle(&philo->second_fork->fork, UNLOCK);
}

/*
wait all philos, synchronize the beginning of the simulation
loop until simulation_finished
	eat
	sleep
	think
*/
void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	
	printf("dinner simulation ");
	printf("philo %d is ready\n", philo->id);
	wait_all_threads_ready(philo->table); //spinlock
	printf("philo %d starts\n", philo->id);
	//set last meal time
	while (!simulation_finished(philo->table))
	{
		if (philo->full)
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

/*
no meals limit; return 0
if only one philo; ad hoc function
else; create all thread, all philo
create all monitor threads
synchronize the beginning of the simulation
	pthread_create -> philo starts running
	every philo start simutaneously
join every one
*/

void	dinner_start(t_table *table)
{
	int	i;
	
	i = -1;
	if (table->nbr_limit_meals == 0)
		return ;
	else if (table->philo_nbr == 1)
	{
		return ; //ad hoc function (TO DO)
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
	printf("dinner_start start_simulation: %ld\n", table->start_simulation);
	//now all threads are ready!
	set_bool(&table->table_mutex, &table->all_threads_ready, true);
	//wait for all threads to finish
	i = -1;
	while (++i < table->philo_nbr)
	{
		safe_thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN);
		printf("philo %d joined\n", i);
	}
	//all threads finished
}
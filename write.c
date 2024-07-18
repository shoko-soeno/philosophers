/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoeno <ssoeno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:37:05 by ssoeno            #+#    #+#             */
/*   Updated: 2024/07/18 18:18:33 by ssoeno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	write_status_debug(t_philo_status status, t_philo *philo, long elapsed)
{
	if(status == TAKE_FIRST_FORK && !simulation_finished(philo->table))
		printf("%-6ld %d has taken the first fork %d\n",
			elapsed, philo->id, philo->first_fork->fork_id);
	if(status == TAKE_SECOND_FORK && !simulation_finished(philo->table))
		printf("%-6ld %d has taken the second fork %d\n",
			elapsed, philo->id, philo->second_fork->fork_id);
	else if (status == EATING && !simulation_finished(philo->table))
		printf("%-6ld %d is eating %ld\n", elapsed, philo->id, philo->meals_counter);
	else if (status == SLEEPING && !simulation_finished(philo->table))
		printf("%-6ld %ld is sleeping %d\n", elapsed, philo->id);
	else if (status == THINKING && !simulation_finished(philo->table))
		printf("%-6ld %ld is thinking %d\n", elapsed, philo->id);
	else if (status == DEAD && !simulation_finished(philo->table))
		printf("%-6ld %ld died %d\n", elapsed, philo->id);
}

void	write_status(t_philo_status status, t_philo *philo, bool debug)
{
	long	elapsed;

	elapsed = gettime(MILLISECOND) - philo->table->start_simulation;

	if(philo->full) //thread safe
	
		return ;
	safe_mutex_handle(&philo->table->write_mutex, LOCK);
	if (debug)
		write_status_debug(status, philo, elapsed);
	else
	{
		if((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
			&& !simulation_finished(philo->table))
			printf("%-6ld %d has taken a fork\n", elapsed, philo->id);
		else if (status == EATING && !simulation_finished(philo->table))
			printf("%-6ld %d is eating\n", elapsed, philo->id);
		else if (status == SLEEPING && !simulation_finished(philo->table))
			printf("%-6ld %d is sleeping\n", elapsed, philo->id);
		else if (status == THINKING && !simulation_finished(philo->table))
			printf("%-6ld %d is thinking\n", elapsed, philo->id);
		else if (status == DEAD && !simulation_finished(philo->table))
			printf("%-6ld %d died\n", elapsed, philo->id);
	}
	safe_mutex_handle(&philo->table->write_mutex, UNLOCK);
}
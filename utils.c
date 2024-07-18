/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoeno <ssoeno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:09:17 by ssoeno            #+#    #+#             */
/*   Updated: 2024/07/18 17:19:04 by ssoeno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* chronometer */
long	gettime(t_timecode time_code)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		error_exit("gettimeofday error");
	if (time_code == SECOND)
		return (time.tv_sec + (time.tv_usec / 1e6));
	if (time_code == MILLISECOND)
		return (time.tv_sec * 1e3 + (time.tv_usec / 1e3));
	if (time_code == MICROSECOND)
		return (time.tv_sec * 1e6 + time.tv_usec);
	else
		error_exit("Invalid time code");
	//return ((long)(time.tv_sec * 1000 + time.tv_usec / 1000));
	return (0);
}

/* presice usleep */
void	precise_usleep(long usec, t_table *table)
{
	long	start_time;
	long	current_time;
	long	remaining;

	start_time = gettime(MICROSECOND);
	current_time = start_time;
	while (current_time - start_time < usec)
	{
		if (simulation_finished(table))
			break ;
		usleep(100);
		current_time = gettime(MICROSECOND);
		remaining = usec - (current_time - start_time);
		//to get a spinlock threshold
		if (remaining < 1000)
			usleep(remaining/2);
		else
		{
			//spinlock
			while (gettime(MICROSECOND) - start_time < usec)
				;
		}
	}
}

void	error_exit(const char *error)
{
	printf("Error: %s\n", error);
	exit(EXIT_FAILURE);
}

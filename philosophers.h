/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoeno <ssoeno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:20:22 by ssoeno            #+#    #+#             */
/*   Updated: 2024/07/16 17:49:35 by ssoeno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <limits.h>
# include <errno.h>

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}		t_opcode;

typedef pthread_mutex_t t_mtx;
typedef struct s_table;

typedef	struct s_fork
{
	t_mtx	fork;
	int		fork_id;
}			t_fork;

typedef struct s_philo
{
	int				id;
	long			meals_counter;
	bool			full;
	long			last_meal_time; //time pass since last meal
	t_fork			*left_fork;
	t_fork			*right_fork_id;
	pthread_t		thread_id; // a philo is a thread
}					t_philo;

typedef struct s_table
{
	long	philo_nbr;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	nbr_limit_meals; //FLAG if -1
	long	start_simulation;
	bool	end_simulation; //all philo die or all ate
	t_fork	*forks;
	t_philo	*philos;
}			t_table;


void	error_exit(const char *error);


#endif
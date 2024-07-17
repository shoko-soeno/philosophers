/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoeno <ssoeno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:20:22 by ssoeno            #+#    #+#             */
/*   Updated: 2024/07/17 18:34:54 by ssoeno           ###   ########.fr       */
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

/* write function macro */
# define DEBUG_MODE 0

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

typedef enum e_timecode
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}		t_timecode;

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DEAD,
}		t_philo_status;

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
	t_fork			*first_fork;
	t_fork			*second_fork;
	t_table			*table;
	t_mtx			philo_mutex; //useful for monitoring
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
	bool	all_threads_ready;
	t_mtx	table_mutex; //avoid races while reading form table
	t_mtx	*write_mutex;
	t_fork	*forks;
	t_philo	*philos;
}			t_table;


void	error_exit(const char *error);

/* handle_functions.c */
void	*safe_malloc(size_t bytes);
void	safe_mutex_handle(t_mtx *mutex, t_opcode opcode);
void	safe_thread_handle(pthread_t *thread, void *(*f)(void *),
		void *data, t_opcode opcode);

/* init.c */
void	data_init(t_table *table);

/* getter_setter.c */
void	set_bool(t_mtx *mutex, bool *dest, bool value);
bool	get_bool(t_mtx *mutex, bool *src);
void	set_long(t_mtx *mutex, long *dest, long value);
long	get_long(t_mtx *mutex, long *src);
bool	simulation_finished(t_table *table);

/* synchro_utils.c */
void	wait_all_threads_ready(t_table *table);

#endif
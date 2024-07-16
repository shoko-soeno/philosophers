/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoeno <ssoeno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:15:00 by ssoeno            #+#    #+#             */
/*   Updated: 2024/07/16 18:55:44 by ssoeno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*safe_malloc(size_t bytes)
{
	void    *ret;

	ret = malloc(bytes);
	if (ret == NULL)
		error_exit("Malloc error");
	return (ret);
}

static void	handle_mutex_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (status == EINVAL &&
		(opcode == LOCK || opcode == UNLOCK || opcode == DESTROY))
		error_exit("The value specified by mutex is invalid");
	else if (status == EINVAL && opcode == INIT)
		error_exit("The value specified by attr is invalid");
	else if (status == EDEADLK)
		error_exit("A deadlock was detected or the current thread owns the mutex");
	else if (status == EPERM)
		error_exit("The current thread does not own the mutex");
	else if (status == ENOMEM)
		error_exit("Insufficient memory exists to initialize the mutex");
	else if (status == EBUSY)
		error_exit("attempt to destroy the object referenced by mutex while it is locked or referenced");
	else if (EAGAIN == status)
		error_exit("Insufficient resources to create another mutex");
	else
		error_exit("Unknown error");
}

void	safe_mutex_handle(t_mtx *mutex, t_opcode opcode)
{
	if (opcode == LOCK)
		handle_mutex_error(pthread_mutex_lock(mutex), opcode);
	else if (opcode == UNLOCK)
		handle_mutex_error(pthread_mutex_unlock(mutex), opcode);
	else if (opcode == INIT)
		handle_mutex_error(pthread_mutex_init(mutex, NULL), opcode);
	else if (opcode == DESTROY)
		handle_mutex_error(pthread_mutex_destroy(mutex), opcode);
	else
		error_exit("Invalid opcode for mutex handle");
}

static void	handle_thread_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (status == EAGAIN)
		error_exit("Insufficient resources to create another thread");
	else if (status == EPERM)
		error_exit("The caller does not have appropriate permission");
	else if (status == EINVAL && opcode == CREATE)
		error_exit("The value specified by attr is invalid");
	else if (status == EINVAL && (opcode == JOIN || opcode == DETACH))
		error_exit("The value specified by thread is invalid");
	else if (status == ESRCH)
		error_exit("No thread with the ID thread could be found");
	else if (status == EDEADLK)
		error_exit("A deadlock was detected");
}

void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *),
		void *data, t_opcode opcode)
{
	if (opcode == CREATE)
		handle_thread_error(pthread_create(thread, NULL, foo, data), opcode);
	else if (opcode == JOIN)
		handle_thread_error(pthread_join(*thread, NULL), opcode);
	else if (opcode == DETACH)
		handle_thread_error(pthread_detach(*thread), opcode);
	else
		error_exit("Invalid opcode for thread handle");
}

void	data_init(t_table *table)
{
	int i;

	i = 0;
	table->end_simulation = false;
	table->philos = safe_malloc(table->philo_nbr);
	
	table->rules.start_time = get_time();
	table->rules.meal_check = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	table->rules.print = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	table->rules.death = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	table->rules.fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * table->rules.num_of_philo);
	if (!table->rules.fork)
		error_exit("Malloc error");
	while (i < table->rules.num_of_philo)
	{
		table->rules.fork[i] = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
		i++;
	}
}

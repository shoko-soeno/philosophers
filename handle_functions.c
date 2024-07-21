/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoeno <ssoeno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:05:07 by ssoeno            #+#    #+#             */
/*   Updated: 2024/07/21 15:45:45 by ssoeno           ###   ########.fr       */
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
	// if (printf("handle_mutex_error: status %d\n", status) < 0) { //debug
    //     fprintf(stderr, "Error: printf failed in handle_mutex_error\n");
    // }
	// fflush(stdout); //debug
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
	{
		// printf("entered if (opcode == LOCK) \n"); //debug
        // printf("mutex address: %p\n", mutex); // デバッグ情報
        int lock_status = pthread_mutex_lock(mutex);
        // printf("pthread_mutex_lock returned: %d\n", lock_status); // デバッグ情報
        handle_mutex_error(lock_status, opcode);
		// handle_mutex_error(pthread_mutex_lock(mutex), opcode);
	}
	else if (opcode == UNLOCK)
		handle_mutex_error(pthread_mutex_unlock(mutex), opcode);
	else if (opcode == INIT)
		handle_mutex_error(pthread_mutex_init(mutex, NULL), opcode);
	else if (opcode == DESTROY)
		handle_mutex_error(pthread_mutex_destroy(mutex), opcode);
	else
		error_exit("Invalid opcode for mutex handle");
	// printf("safe_mutex_handle: mutex %p\n", mutex); //debug
	// fflush(stdout); //debug
	return ;
}

static void	handle_thread_error(int status, t_opcode opcode)
{
	printf("handle_thread_error: status %d\n", status); //debug
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

void	safe_thread_handle(pthread_t *thread, void *(*f)(void *),
		void *data, t_opcode opcode)
{
	printf("safe_thread_handle: thread %p\n", thread); //debug
	printf("safe_thread_handle: opcode %d\n", opcode); //debug
	int result;
	
	if (opcode == CREATE)
		handle_thread_error(pthread_create(thread, NULL, f, data), opcode);
	else if (opcode == JOIN)
	{
		printf("JOIN\n"); //debug
		fflush(stdout); //debug
		printf("safe_thread_handle: pthread_join thread %p\n", thread); //debug
		result = pthread_join(*thread, NULL); //debug
		printf("safe_thread_handle: pthread_join returned: %d\n", result); //debug
		//handle_thread_error(pthread_join(*thread, NULL), opcode);
	}
	else if (opcode == DETACH)
		handle_thread_error(pthread_detach(*thread), opcode);
	else
		error_exit("Invalid opcode for thread handle");
}
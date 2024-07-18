/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter_setter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoeno <ssoeno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:47:36 by ssoeno            #+#    #+#             */
/*   Updated: 2024/07/18 17:30:44 by ssoeno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//BOOL
void	set_bool(t_mtx *mutex, bool *dest, bool value)
{
	safe_mutex_handle(mutex, LOCK);
	*dest = value;
	safe_mutex_handle(mutex, UNLOCK);
}

bool	get_bool(t_mtx *mutex, bool *src)
{
	bool	ret;

	safe_mutex_handle(mutex, LOCK);
	ret = *src;
	safe_mutex_handle(mutex, UNLOCK);
	return (ret);
}

//LONG
void	set_long(t_mtx *mutex, long *dest, long value)
{
	safe_mutex_handle(mutex, LOCK);
	*dest = value;
	safe_mutex_handle(mutex, UNLOCK);
}

long	get_long(t_mtx *mutex, long *src)
{
	bool	ret;

	safe_mutex_handle(mutex, LOCK);
	ret = *src;
	safe_mutex_handle(mutex, UNLOCK);
	return (ret);
}

bool	simulation_finished(t_table *table)
{
	return (get_bool(&table->table_mutex, &table->end_simulation));
}
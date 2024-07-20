/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchro_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoeno <ssoeno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:55:44 by ssoeno            #+#    #+#             */
/*   Updated: 2024/07/20 16:12:16 by ssoeno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//spinlock to synchronize philos starts
void	wait_all_threads_ready(t_table *table)
{
	printf("outside loop; waiting for all threads to be ready\n"); //debug
	while (!get_bool(&table->table_mutex, &table->all_threads_ready))
	{
		printf("inside loop; waiting for all threads to be ready\n"); //debug
		;
	}
}
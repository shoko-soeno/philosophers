/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoeno <ssoeno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:15:00 by ssoeno            #+#    #+#             */
/*   Updated: 2024/07/04 18:18:19 by ssoeno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int init_mutex(t_rules *rules)
{
    int i;

    i = rules->nb_philosophers;
    while (--i >= 0)
    {
        if (pthread_mutex_init(&rules->fork[i], NULL))
            return (error_handling(5));
    }
    if (pthread_mutex_init(&rules->meal_check, NULL))
        return (error_handling(5));
    if (pthread_mutex_init(&rules->writing, NULL))
        return (error_handling(5));
    return (0);
}

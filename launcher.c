/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoeno <ssoeno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:18:52 by ssoeno            #+#    #+#             */
/*   Updated: 2024/07/04 18:30:17 by ssoeno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void    philo_eats(t_philo *philo)
{
    t_rules *rules;

    rules = philo->rules;
    pthread_mutex_lock(&rules->fork[phile->left_fork_id]);
    action_print(rules, phile->id, "has taken a fork");
    pthread_mutex_lock(&rules->fork[phile->right_fork_id]);
    action_print(rules, philo->id, "has taken a fork");
    philo->t_last_meal = get_time();
    pthread_mutex_unlock(&rules->meal_check);
    smart_sleep(rules->time_to_eat, rules);
    (philo->x_ate)++;
    pthread_mutex_unlock(&rules->fork[philo->left_fork_id]);
    pthread_mutex_unlock(&rules->fork[philo->right_fork_id]);   
}

void    *p_thread()
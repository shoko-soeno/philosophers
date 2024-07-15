/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoeno <ssoeno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:20:22 by ssoeno            #+#    #+#             */
/*   Updated: 2024/07/04 18:04:46 by ssoeno           ###   ########.fr       */
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

typedef pthread_mutex_t t_mtx;

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
	long			last_meal_time;
	t_fork				left_fork;
	t_fork				right_fork_id;
	pthread_t		thread_id;
}					t_philo;

typedef struct s_table
{
	long	philo_nbr;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	nbr_limit_meals;
	long	start_simulation;
	bool	end_simulation;
	t_fork	*forks;
	t_philo	*philo;
}			t_table;

typedef struct s_rules
{
	int				nb_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_must_eat;
	int				dead;
	int				all_ate;
	long long		first_timestamp;
	pthread_mutex_t	meal_check;
	pthread_mutex_t	fork[250];
	pthread_mutex_t	writing;
	t_philo			philosophers[250];
}					t_rules;

int					write_error(char *str);
int					error_handling(int error);

int					init_all(t_rules *rules, char **av);

int					ft_atoi(const char *str);
void				action_print(t_rules *rules, int id, char *str);
long long			get_time(void);
long long			time_diff(long long past, long long pres);
void				smart_spleep(long long time, t_rules *rules);

int					launcher(t_rules *rules);
void				exit_launcher(t_rules *rules, t_philo *philos);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoeno <ssoeno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:41:13 by ssoeno            #+#    #+#             */
/*   Updated: 2024/07/16 16:15:09 by ssoeno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static long	ft_atol(const char *str)
{
	long	ret;
	long	sign;

	ret = 0l;
	sign = 1l;
	while ((9 <= *str && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign = -1l;
	while (ft_isdigit(*str))
	{
		if (ret > LONG_MAX / 10 || (ret == LONG_MAX / 10 && *str > '7'))
			return (LONG_MAX);
		if (ret < LONG_MIN / 10 || (ret == LONG_MIN / 10 && *str > '8'))
			return (LONG_MIN);
		ret = ret * 10l + (*str++ - '0') * sign;
	}
	return (ret);
}

bool	ft_is_positive_num(char *num)
{
	size_t	i;

	i = 0;
	if (num[0] == '-')
		return (false);
	if (num[0] == '+')
		i++;
	if (num[i] == '\0')
		return (false);
	while (num[i])
	{
		if (!ft_isdigit(num[i]))
			return (false);
		i++;
	}
	return (true);
}
/* ./philo
timestamps > 60 ms
USLEEP function want usec
*/

void    parse_input(t_table *table, char **av)
{
	table->philo_nbr = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]) * 1e3; //milli seconds to micro seconds
	table->time_to_eat = ft_atol(av[3]) * 1e3;
	table->time_to_sleep = ft_atol(av[4]) * 1e3;
	if (table->time_to_die < 6e4 || table->time_to_eat < 6e4
		|| table->time_to_sleep < 6e4)
		error_exit("Time must be greater than 60 ms");
	if (av[5])
		table->nbr_limit_meals = ft_atol(av[5]);
	else
		table->nbr_limit_meals = -1;	
}

bool	ft_check_args(int argc, char **argv)
{
	int		i;
	long	tmp;
	char	**args;

	i = 0;
	if (argc == 2)
		args = ft_split(argv[1], ' ');
	else
		args = argv + 1;
	i = 0;
	while (args[i])
	{
		tmp = ft_atol(args[i]);
		if (!ft_isnum(args[i]) || ft_duplicate(tmp, args, i)
			|| tmp < INT_MIN || tmp > INT_MAX)
		{
			if (argc == 2)
				ft_free(args);
			return (false);
		}
		i++;
	}
	if (argc == 2)
		ft_free(args);
	return (true);
}
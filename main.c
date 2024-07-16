/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoeno <ssoeno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:06:29 by ssoeno            #+#    #+#             */
/*   Updated: 2024/07/16 17:34:36 by ssoeno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	main(int ac, char **av)
{
	t_table	table;

	if (ac == 5 || ac == 6)
	{
		parse_input(&table, av);
		data_init(&table);
		dinner_start(&table);
		clean(&table);
	} else
	{
		error_exit("Input example: ./philo 5 800 200 200");
	}
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoeno <ssoeno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:05:13 by ssoeno            #+#    #+#             */
/*   Updated: 2024/07/04 18:17:25 by ssoeno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int write_error(char *str)
{
    int len;

    len = 0;
    while (str[len])
        len++;
    write(2, "Error: ", 7);
    write(2, str, len);
    write(2, "\n", 1);
    return (1);
}

int error_handling(int error)
{
    if (error == 1)
        return (write_error("Wrong number of arguments"));
    if (error == 2)
        return (write_error("Invalid argument"));
    if (error == 3)
        return (write_error("Malloc error"));
    if (error == 4)
        return (write_error("Thread error"));
    if (error == 5)
        return (write_error("Mutex error"));
    return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:53:07 by uschmidt          #+#    #+#             */
/*   Updated: 2025/02/26 13:53:09 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "utils.h"

int	ft_atoi(const char *nptr)
{
	int	neg;
	int	result;

	neg = 1;
	result = 0;
	while (*nptr == ' ' || *nptr == '\f' || *nptr == '\n'
		|| *nptr == '\r' || *nptr == '\t' || *nptr == '\v')
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			neg = -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		result = result * 10 + *nptr - '0';
		nptr++;
	}
	return (result * neg);
}

int	on_error(int err)
{
	errno = err;
	printf("Error: %s\n", strerror(errno));
	return (errno);
}

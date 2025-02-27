/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:53:07 by uschmidt          #+#    #+#             */
/*   Updated: 2025/02/27 16:26:08 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "utils.h"
#include "../includes/constants.h"

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

int	on_error(int err, t_prog prog)
{
	errno = err;
	clean_up(prog);
	printf("Error: %s\n", strerror(errno));
	return (errno);
}

void	clean_up(t_prog prog)
{
	int	i;

	i = 0;
	pthread_exit(NULL);
	free(prog.tids);
	free(prog.phils);
	i = 0;
	while (i < prog.n_phils)
		pthread_mutex_destroy(&prog.forks[i]);
	free(prog.forks);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:53:07 by uschmidt          #+#    #+#             */
/*   Updated: 2025/05/30 10:44:39 by uschmidt         ###   ########.fr       */
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

void	clean_up(t_prog prog, t_app_state state)
{
	int	i;

	if (state < PROG_INIT)
		return ;
	free(prog.tids);
	if (state < THREAD_INIT)
		return ;
	i = 0;
	while (i < prog.n_phils)
		free(prog.phils[i++]);
	free(prog.phils);
}

void	clean_mutexes(t_prog prog)
{
	int	i;

	i = 0;
	while (i < prog.n_phils)
	{
		pthread_mutex_destroy(prog.forks[i]);
		free(prog.forks[i]);
		pthread_mutex_destroy(prog.status_locks[i]);
		free(prog.status_locks[i++]);
	}
	free(prog.forks);
	free(prog.status_locks);
	pthread_mutex_destroy(prog.init_lock);
	free(prog.init_lock);
	pthread_mutex_destroy(prog.print_lock);
	free(prog.print_lock);
}

//returns time in milliseconds
long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

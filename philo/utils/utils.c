/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:53:07 by uschmidt          #+#    #+#             */
/*   Updated: 2025/03/04 13:49:04 by uschmidt         ###   ########.fr       */
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

int	on_error(int err, t_prog prog, t_app_state state)
{
	errno = err;
	clean_up(prog, state);
	printf("Error: %s\n", strerror(errno));
	return (errno);
}

//TODO: Add clean_up states
void	clean_up(t_prog prog, t_app_state state)
{
	int	i;

	i = 0;
	if (state < PROG_INIT)
		return ;
	free(prog.tids);
	if (state < THREAD_INIT)
		return ;
	free(prog.phils);
	i = 0;
	while (i < prog.n_phils)
		pthread_mutex_destroy(&prog.forks[i]);
	free(prog.forks);
	pthread_exit(NULL);
}

int	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	is_arg_valid(char **argv)
{
	int		i;
	char	*argv_curr;

	i = 0;
	argv++;
	while (*argv)
	{
		argv_curr = *argv;
		while (argv_curr[i])
		{
			if (!(argv_curr[i] >= '0' && argv_curr[i] <= '9'))
				return (0);
			i++;
		}
		argv++;
		i = 0;
	}
	return (1);
}

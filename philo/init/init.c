/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:35:32 by uschmidt          #+#    #+#             */
/*   Updated: 2025/02/27 16:32:15 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/constants.h"
#include "init.h"

int	init_prog(char **argv, t_prog *prog)
{
	prog->n_phils = ft_atoi(argv[1]);
	prog->time_to_die = ft_atoi(argv[2]);
	prog->time_to_eat = ft_atoi(argv[3]);
	prog->time_to_sleep = ft_atoi(argv[4]);
	prog->phil_id = 0;
	if (argv[5])
		prog->n_meals = ft_atoi(argv[5]);
	else
		prog->n_meals = 0;
	return (0);
}

int	init_threads(int n_phils, pthread_t **tid, t_phil **phils)
{
	*tid = (pthread_t *)malloc(sizeof(pthread_t) * n_phils);
	if (!(*tid))
		return (errno);
	*phils = (t_phil *)malloc(sizeof(t_phil) * n_phils);
	if (!(*tid))
	{
		free(*tid);
		return (errno);
	}
	return (0);
}

int	init_forks(int n_phils, pthread_mutex_t **forks, pthread_mutex_t *init_lock)
{
	*forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * n_phils);
	if (!(*forks))
		return (errno);
	init_lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!init_lock)
	{
		free(forks);
		return (errno);
	}
	return (0);
}

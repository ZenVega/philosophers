/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:35:32 by uschmidt          #+#    #+#             */
/*   Updated: 2025/03/04 14:01:03 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	init_threads(int n_phils, pthread_t **tid, t_prog *prog)
{
	*tid = (pthread_t *)malloc(sizeof(pthread_t) * n_phils);
	if (!(*tid))
		return (errno);
	prog->phils = (t_phil *)malloc(sizeof(t_phil) * n_phils);
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

void	init_phils(t_prog *prog)
{
	t_phil	phil;
	int		i;

	i = -1;
	while (i++ < prog->n_phils - 1)
	{
		phil.id = i;
		phil.status = THINK;
		phil.meals = 0;
		phil.fork_1 = prog->forks[phil.id];
		if (phil.id >= prog->n_phils)
			phil.fork_2 = prog->forks[0];
		else
			phil.fork_2 = prog->forks[phil.id + 1];
		log_action(phil.id, INIT);
		phil.alive = 1;
		prog->phils[i] = phil;
	}
	prog->running = 1;
}

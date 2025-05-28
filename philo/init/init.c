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
#include <stdio.h>
#include "init.h"

int	init_prog(char **argv, t_prog *prog)
{
	prog->n_phils = ft_atoi(argv[1]);
	if (prog->n_phils < 2)
		return (EINVAL);
	prog->start_time = get_time();
	prog->time_to_die = ft_atoi(argv[2]);
	prog->time_to_eat = ft_atoi(argv[3]);
	prog->time_to_sleep = ft_atoi(argv[4]);
	prog->phil_id = 0;
	prog->running = 1;
	prog->init_lock = NULL;
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
	prog->phils = (t_phil **)malloc(sizeof(t_phil *) * n_phils);
	if (!(prog->phils))
	{
		free(*tid);
		return (errno);
	}
	return (0);
}

int	init_forks(t_prog *prog)
{
	int	i;

	i = 0;
	prog->forks = (pthread_mutex_t *)malloc(
			sizeof(pthread_mutex_t) * prog->n_phils);
	if (!(prog->forks))
		return (errno);
	while (i < prog->n_phils)
		pthread_mutex_init(&(prog->forks)[i++], NULL);
	prog->init_lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	prog->dead_lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!(prog->init_lock) || !(prog->dead_lock))
	{
		free(prog->dead_lock);
		free(prog->init_lock);
		free(prog->forks);
		return (errno);
	}
	pthread_mutex_init(prog->init_lock, NULL);
	pthread_mutex_init(prog->dead_lock, NULL);
	return (0);
}

void	init_phils(t_prog *prog)
{
	t_phil	*phil;
	int		i;

	i = 0;
	while (i < prog->n_phils)
	{
		phil = (t_phil *)malloc(sizeof(t_phil));
		phil->id = i;
		phil->status = THINK;
		phil->meals = 0;
		phil->fork_1 = &prog->forks[phil->id];
		if (phil->id == prog->n_phils - 1)
			phil->fork_2 = &prog->forks[0];
		else
			phil->fork_2 = &prog->forks[phil->id + 1];
		phil->born = 0;
		prog->phils[i] = phil;
		i++;
	}
}

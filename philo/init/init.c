/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:35:32 by uschmidt          #+#    #+#             */
/*   Updated: 2025/05/30 11:46:04 by uschmidt         ###   ########.fr       */
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
	prog->print_lock = NULL;
	prog->status_locks = NULL;
	prog->forks = NULL;
	prog->dead_lock = NULL;
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

static int	create_mutex_arr(t_prog *prog, pthread_mutex_t ***address)
{
	int	i;

	i = 0;
	*address = (pthread_mutex_t **)malloc(
			sizeof(pthread_mutex_t) * prog->n_phils);
	if (!(*address))
		return (errno);
	while (i < prog->n_phils)
	{
		(*address)[i] = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		if (!(*address)[i])
			return (errno);
		pthread_mutex_init((*address)[i++], NULL);
	}
	return (0);
}

int	init_mutexes(t_prog *prog)
{
	int	err;

	err = create_mutex_arr(prog, &prog->forks); 
	if (err)
		return (err);
	err = create_mutex_arr(prog, &prog->status_locks); 
	if (err)
		return (err);
	prog->init_lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	prog->dead_lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	prog->print_lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!(prog->init_lock) || !(prog->dead_lock) || !(prog->print_lock))
		return (errno);
	pthread_mutex_init(prog->init_lock, NULL);
	pthread_mutex_init(prog->dead_lock, NULL);
	pthread_mutex_init(prog->print_lock, NULL);
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
		phil->status_lock = prog->status_locks[phil->id];
		phil->fork_1 = prog->forks[phil->id];
		if (phil->id == prog->n_phils - 1)
			phil->fork_2 = prog->forks[0];
		else
			phil->fork_2 = prog->forks[phil->id + 1];
		phil->born = 0;
		prog->phils[i] = phil;
		i++;
	}
}

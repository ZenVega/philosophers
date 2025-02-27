/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:04:49 by uschmidt          #+#    #+#             */
/*   Updated: 2025/02/27 17:20:54 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
#include <signal.h>

static t_phil	init_phil(t_prog *prog, int id)
{
	t_phil	phil;

	phil.id = id;
	phil.last_meal = prog->time_to_die;
	phil.status = THINK;
	phil.meals = 0;
	phil.fork_1 = prog->forks[phil.id];
	if (phil.id >= prog->n_phils)
		phil.fork_2 = prog->forks[0];
	else
		phil.fork_2 = prog->forks[phil.id + 1];
	printf("ID: %lu\n", pthread_self());
	log_action(phil.id, INIT);
	phil.alive = 1;
	return (phil);
}

static void	grab_fork(t_phil *phil)
{
	int				fork_1_grabbed;
	int				fork_2_grabbed;

	fork_1_grabbed = !pthread_mutex_lock(&phil->fork_1);
	if (fork_1_grabbed)
		fork_2_grabbed = !pthread_mutex_lock(&phil->fork_2);
	if (!fork_2_grabbed)
		pthread_mutex_unlock(&phil->fork_1);
	else
	{
		phil->status = EAT;
		phil->meals++;
		log_action(phil->id, phil->status);
		phil->last_meal = get_time();
	}
}

static void	finish_meal(t_phil *phil, int time_to_eat)
{
	if (get_time() - phil->last_meal >= time_to_eat)
	{
		pthread_mutex_unlock(&phil->fork_1);
		pthread_mutex_unlock(&phil->fork_2);
		phil->status = SLEEP;
		log_action(phil->id, phil->status);
		phil->last_nap = get_time();
	}
}

static void	wake_up(t_phil *phil, int time_to_sleep)
{
	if (get_time() - phil->last_nap >= time_to_sleep)
	{
		pthread_mutex_unlock(&phil->fork_1);
		pthread_mutex_unlock(&phil->fork_2);
		phil->status = SLEEP;
		log_action(phil->id, phil->status);
		phil->last_nap = get_time();
	}
}

void	*create_phil(void *data)
{
	t_prog		*prog;
	t_phil		*phil;
	int			id;

	prog = (t_prog *)data;
	pthread_mutex_lock(&prog->init_lock);
	id = prog->phil_id++;
	prog->phils[id] = init_phil(prog, id);
	phil = &prog->phils[id];
	while (phil->alive)
	{
		if (phil->status == THINK)
			grab_fork(phil);
		else if (phil->status == EAT)
			finish_meal(phil, prog->time_to_eat);
		else if (phil->status == SLEEP)
			wake_up(phil, prog->time_to_sleep);
		if (prog->n_meals && (&prog->phils[prog->n_phils-1] != NULL) && all_eaten(prog))
		{
			printf("Everyone Lives\n");
			return (NULL);
		}
	}
	log_action(phil->id, DEAD);
	pthread_mutex_unlock(&prog->init_lock);
	return (NULL);
}

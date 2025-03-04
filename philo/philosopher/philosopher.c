/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:04:49 by uschmidt          #+#    #+#             */
/*   Updated: 2025/03/04 14:20:12 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	grab_fork(t_phil *phil)
{
	//TODO: phils share forks, why?
	if (phil->id % 2 == 0)
	{
		pthread_mutex_lock(&phil->fork_1);
		pthread_mutex_lock(&phil->fork_2);
	}
	else
	{
		pthread_mutex_lock(&phil->fork_2);
		pthread_mutex_lock(&phil->fork_1);
	}
	phil->status = EAT;
	phil->meals++;
	log_action(phil->id, phil->status);
	phil->last_meal = get_time();
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
		phil->status = THINK;
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
	phil = &prog->phils[id];
	phil->last_meal = get_time();
	pthread_mutex_unlock(&prog->init_lock);
	while (prog->running && phil->alive)
	{
		while (prog->running && phil->status == THINK)
			grab_fork(phil);
		while (prog->running && phil->status == EAT)
			finish_meal(phil, prog->time_to_eat);
		while (prog->running && phil->status == SLEEP)
			wake_up(phil, prog->time_to_sleep);
	}
	if (!phil->alive)
		log_action(id, DEAD);
	pthread_detach(pthread_self());
	return (NULL);
}

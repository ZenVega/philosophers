/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:04:49 by uschmidt          #+#    #+#             */
/*   Updated: 2025/05/30 11:25:58 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	grab_forks(t_prog *prog, t_phil *phil,
		pthread_mutex_t *fork_1, pthread_mutex_t *fork_2)
{
	pthread_mutex_lock(fork_1);
	log_action(prog, phil->id, FORK, get_time());
	pthread_mutex_lock(fork_2);
	log_action(prog, phil->id, FORK, get_time());
}

static void	phil_eat(t_prog *prog, t_phil *phil)
{
	pthread_mutex_lock(phil->status_lock);
	if (phil->status == DEAD)
	{
		pthread_mutex_unlock(phil->status_lock);
		return ;
	}
	if (!(phil->id % 2))
		grab_forks(prog, phil, phil->fork_1, phil->fork_2);
	else
		grab_forks(prog, phil, phil->fork_2, phil->fork_1);
	phil->last_meal = get_time();
	phil->status = EAT;
	pthread_mutex_unlock(phil->status_lock);
	log_action(prog, phil->id, EAT, phil->last_meal);
	usleep(prog->time_to_eat * 1000);
	pthread_mutex_unlock(phil->fork_1);
	pthread_mutex_unlock(phil->fork_2);
}

static void	phil_sleep(t_prog *prog, t_phil *phil)
{
	pthread_mutex_lock(phil->status_lock);
	if (phil->status == DEAD)
	{
		pthread_mutex_unlock(phil->status_lock);
		return ;
	}
	phil->status = SLEEP;
	pthread_mutex_unlock(phil->status_lock);
	log_action(prog, phil->id, SLEEP, get_time());
	usleep(prog->time_to_sleep * 1000);
}

static void	phil_think(t_prog *prog, t_phil *phil)
{
	//TODO: how to time thinking properly??
	long	time_sleep;
	long	time;

	pthread_mutex_lock(phil->status_lock);
	phil->status = THINK;
	pthread_mutex_unlock(phil->status_lock);
	time = get_time();
	log_action(prog, phil->id, THINK, time);
	time_sleep = (prog->time_to_eat - prog->time_to_sleep);
	if (time_sleep > 0)
		usleep(time_sleep * 1000);
	else
		usleep(-time_sleep * 1000);
}

void	*create_phil(void *data)
{
	t_prog		*prog;
	t_phil		*phil;

	prog = (t_prog *)data;
	pthread_mutex_lock(prog->init_lock);
	phil = prog->phils[prog->phil_id++];
	pthread_mutex_unlock(prog->init_lock);
	if (!(phil->id % 2))
	{
		log_action(prog, phil->id, THINK, get_time());
		usleep(1000);
	}
	pthread_mutex_lock(phil->status_lock);
	phil->last_meal = get_time();
	pthread_mutex_unlock(phil->status_lock);
	while (1)
	{
		pthread_mutex_lock(prog->dead_lock);
		if (!prog->running)
			break ;
		pthread_mutex_unlock(prog->dead_lock);
		phil_eat(prog, phil);
		phil_sleep(prog, phil);
		phil_think(prog, phil);
		pthread_mutex_lock(phil->status_lock);
		if (phil->status == DEAD)
			break ;
		pthread_mutex_unlock(phil->status_lock);
	}
	return (NULL);
}

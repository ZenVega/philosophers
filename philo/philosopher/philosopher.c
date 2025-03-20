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

static void	grab_fork(t_phil *phil, int time_to_eat)
{
	pthread_mutex_lock(&phil->fork_1);
	log_action(phil->id, FORK);
	pthread_mutex_lock(&phil->fork_2);
	log_action(phil->id, FORK);
	phil->status = EAT;
	phil->meals++;
	log_action(phil->id, phil->status);
	phil->last_meal = get_time();
	usleep(time_to_eat);
}

static void	finish_meal(t_phil *phil, int time_to_sleep)
{
	pthread_mutex_unlock(&phil->fork_1);
	pthread_mutex_unlock(&phil->fork_2);
	phil->status = SLEEP;
	log_action(phil->id, phil->status);
	phil->last_nap = get_time();
	usleep(time_to_sleep);
}

static void	wake_up(t_phil *phil)
{
	phil->status = THINK;
	log_action(phil->id, phil->status);
}

//TODO: Dying phil doesn't close thread
void	*create_phil(void *data)
{
	t_prog		*prog;
	t_phil		*phil;
	int			id;
	int			offset;

	prog = (t_prog *)data;
	pthread_mutex_lock(prog->init_lock);
	id = prog->phil_id++;
	phil = prog->phils[id];
	pthread_mutex_unlock(prog->init_lock);
	offset = 0;
	if (id % 2)
		offset = prog->time_to_eat; 
	usleep(offset);
	phil->last_meal = get_time();
	phil->last_nap = get_time();
	phil->born = 1;
	printf("THREAD %d STARTED @ %ld\n", id, get_time());
	while (prog->running && phil->alive)
	{
		while (prog->running && phil->status == THINK)
			grab_fork(phil, prog->time_to_eat);
		while (prog->running && phil->status == EAT)
			finish_meal(phil, prog->time_to_sleep);
		while (prog->running && phil->status == SLEEP)
			wake_up(phil);
	}
	if (!phil->alive)
		log_action(id, DEAD);
	printf("THREAD %d CLOSED\n", id);
	return (NULL);
}

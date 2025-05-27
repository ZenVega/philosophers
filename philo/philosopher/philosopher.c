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

static void	grab_fork(t_phil *phil, t_prog *prog)
{
	if (phil->id % 2)
	{
		pthread_mutex_lock(phil->fork_1);
		log_action(prog, phil->id, FORK);
	}
	pthread_mutex_lock(phil->fork_2);
	log_action(prog, phil->id, FORK);
	if (!(phil->id % 2))
	{
		pthread_mutex_lock(phil->fork_1);
		log_action(prog, phil->id, FORK);
	}
	phil->status = EAT;
	phil->meals++;
	log_action(prog, phil->id, phil->status);
	phil->last_meal = get_time();
	usleep(prog->time_to_eat * 1000);
}

static void	finish_meal(t_phil *phil, t_prog *prog)
{
	pthread_mutex_unlock(phil->fork_1);
	pthread_mutex_unlock(phil->fork_2);
	phil->status = SLEEP;
	log_action(prog, phil->id, phil->status);
	phil->last_nap = get_time();
	usleep(prog->time_to_sleep * 1000);
}

static void	wake_up(t_phil *phil, t_prog *prog)
{
	phil->status = THINK;
	log_action(prog, phil->id, phil->status);
}

void	*create_phil(void *data)
{
	t_prog		*prog;
	t_phil		*phil;
	int			id;
	int			offset;

	prog = (t_prog *)data;
	pthread_mutex_lock(prog->init_lock);
	phil = prog->phils[prog->phil_id++];
	id = phil->id;
	pthread_mutex_unlock(prog->init_lock);
	offset = 0;
	if (id % 2)
		offset = prog->time_to_eat; 
	usleep(offset * 1000);
	printf("IDS %d / %d\n", id, phil->id);
	phil->last_meal = get_time();
	phil->last_nap = get_time();
	phil->born = 1;
	while (prog->running && phil->status != DEAD)
	{
		if (phil->status == THINK)
			grab_fork(phil, prog);
		if (phil->status == EAT)
			finish_meal(phil, prog);
		if (phil->status == SLEEP)
			wake_up(phil, prog);
	}
	if (phil->status == DEAD)
		log_action(prog, phil->id, phil->status);
	printf("PHIL %d exit\n", phil->id);
	return (NULL);
}

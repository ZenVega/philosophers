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
	if (phil->id % 2)
		grab_forks(prog, phil, phil->fork_1, phil->fork_2);
	else
		grab_forks(prog, phil, phil->fork_2, phil->fork_1);
	phil->status = EAT;
	phil->last_meal = get_time();
	log_action(prog, phil->id, EAT, phil->last_meal);
	usleep(prog->time_to_eat * 1000);
}

static void	phil_sleep(t_prog *prog, t_phil *phil)
{
	phil->status = SLEEP;
	log_action(prog, phil->id, SLEEP, get_time());
	usleep(prog->time_to_sleep * 1000);
}

static void	phil_think(t_prog *prog, t_phil *phil)
{
	long	time_think;

	phil->status = THINK;
	log_action(prog, phil->id, THINK, get_time());
	time_think = prog->time_to_die - (get_time() - phil->last_meal);
	if (time_think > 0)
		usleep((time_think - 50) * 1000);
}

void	*create_phil(void *data)
{
	t_prog		*prog;
	t_phil		*phil;

	prog = (t_prog *)data;
	pthread_mutex_lock(prog->init_lock);
	phil = prog->phils[prog->phil_id++];
	phil->last_meal = get_time();
	pthread_mutex_unlock(prog->init_lock);
	while (1)
	{
		if (!prog->running)
			break ;
		if (phil->status == THINK)
			phil_eat(prog, phil);
		if (phil->status == EAT)
			phil_sleep(prog, phil);
		if (phil->status == SLEEP)
			phil_think(prog, phil);
		if (phil->status == DEAD)
			break ;
	}
	return (NULL);
}

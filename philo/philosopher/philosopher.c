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
		phil->status = THINK;
		log_action(phil->id, phil->status);
		phil->last_nap = get_time();
	}
}

int	is_dead(t_phil *phil, int time_to_die)
{
	int	time;

	time = get_time();
	if (time - phil->last_meal > time_to_die)
	{
		phil->alive = 0;
		return (1);
	}
	return (0);
}

void	*create_phil(void *data)
{
	t_prog		*prog;
	t_phil		*phil;
	int			id;
	int			i;
//TODO: Surveillance shoould be another thread
//TODO: data should only be the id
	prog = (t_prog *)data;
	pthread_mutex_lock(&prog->init_lock);
	id = prog->phil_id++;
	phil = &prog->phils[id];
	pthread_mutex_unlock(&prog->init_lock);
	while (phil->alive)
	{
		if (is_dead(phil, prog->time_to_die))
			break ;
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
		i = 0;
		while (i < prog->n_phils)
			if (!prog->phils[i++].alive)
				break ;
	}
	log_action(phil->id, DEAD);
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:04:49 by uschmidt          #+#    #+#             */
/*   Updated: 2025/02/27 12:30:03 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	init_phil(t_phil *phil, t_state *state)
{
	phil->id = state->phil_id++;
	phil->last_meal = state->time_to_die;
	phil->status = THINK;
	phil->fork_1 = state->forks[phil->id];
	if (phil->id >= state->n_phils)
		phil->fork_2 = state->forks[0];
	else
		phil->fork_2 = state->forks[phil->id + 1];
	printf("ID: %lu\n", pthread_self());
	log_action(phil->id, INIT);
	phil->alive = 1;
}

static void	grab_fork(int n_phils, pthread_mutex_t *forks, t_phil *phil)
{
	int				fork_1_grabbed;
	int				fork_2_grabbed;

	fork_1_grabbed = pthread_mutex_lock(&phil->fork_1);
	if (!fork_1_grabbed)
		fork_2_grabbed = pthread_mutex_lock(&phil->fork_2);
	if (fork_2_grabbed)
		pthread_mutex_unlock(&phil->fork_1);
	else
	{
		phil->status = EAT;
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
	t_state		*state;
	t_phil		phil;

	state = (t_state *)data;
	init_phil(&phil, state);
	while (phil.alive)
	{
		if (phil.status == THINK)
			grab_fork(state->n_phils, state->forks, &phil);
		else if (phil.status == EAT)
			finish_meal(&phil, state->time_to_eat);
		else if (phil.status == SLEEP)
			wake_up(&phil, state->time_to_sleep);
	}
	log_action(phil.id, DEAD);
	return (0);
}

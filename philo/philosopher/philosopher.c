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

static int	p_running(t_prog *prog)
{
	pthread_mutex_lock(prog->dead_lock);
	if (!prog->running)
	{
		pthread_mutex_unlock(prog->dead_lock);
		return (0);
	}
	pthread_mutex_unlock(prog->dead_lock);
	return (1);
}

static void	grab_forks(t_phil *phil, t_prog *prog)
{

	if (phil->id % 2)
	{
		pthread_mutex_lock(phil->fork_1);
		log_action(prog, phil->id, FORK);
		if (!p_running(prog))
		{
			pthread_mutex_unlock(phil->fork_1);
			return ;
		}
		pthread_mutex_lock(phil->fork_2);
		log_action(prog, phil->id, FORK);
	}
	else 
	{
		pthread_mutex_lock(phil->fork_2);
		log_action(prog, phil->id, FORK);
		if (!p_running(prog))
		{
			pthread_mutex_unlock(phil->fork_1);
			return ;
		}
		pthread_mutex_lock(phil->fork_1);
		log_action(prog, phil->id, FORK);
	}
	if (!p_running(prog))
	{
		pthread_mutex_unlock(phil->fork_1);
		pthread_mutex_unlock(phil->fork_2);
		return ;
	}
}

static void	start_eating(t_phil *phil, t_prog *prog)
{
	grab_forks(phil, prog);
	pthread_mutex_lock(prog->init_lock);
	phil->status = EAT;
	phil->meals++;
	log_action(prog, phil->id, phil->status);
	phil->last_meal = get_time();
	pthread_mutex_unlock(prog->init_lock);
	usleep(prog->time_to_eat * 1000);
}

static void	finish_meal(t_phil *phil, t_prog *prog)
{
	pthread_mutex_unlock(phil->fork_1);
	pthread_mutex_unlock(phil->fork_2);
	pthread_mutex_lock(prog->init_lock);
	phil->status = SLEEP;
	pthread_mutex_unlock(prog->init_lock);
	log_action(prog, phil->id, phil->status);
	phil->last_nap = get_time();
	usleep(prog->time_to_sleep * 1000);
}

static void	wake_up(t_phil *phil, t_prog *prog)
{
	long	sleep;

	pthread_mutex_lock(prog->init_lock);
	phil->status = THINK;
	log_action(prog, phil->id, phil->status);
	pthread_mutex_unlock(prog->init_lock);
	sleep = prog->time_to_die - (get_time() - phil->last_meal);
	if (sleep > 0)
		usleep(sleep * 500);
}

void	*create_phil(void *data)
{
	t_prog		*prog;
	t_phil		*phil;
	int			id;
	int			status;

	prog = (t_prog *)data;
	pthread_mutex_lock(prog->init_lock);
	phil = prog->phils[prog->phil_id++];
	id = phil->id;
	phil->last_meal = get_time();
	phil->last_nap = get_time();
	phil->born = 1;
	pthread_mutex_unlock(prog->init_lock);
	if (!(id % 2))
	{
		log_action(prog, phil->id, phil->status);
		usleep(1000);
	}
	while (1)
	{
		if (!p_running(prog))
			break;
		pthread_mutex_lock(prog->init_lock);
		status = phil->status;
		pthread_mutex_unlock(prog->init_lock);
		if (status == THINK)
			start_eating(phil, prog);
		else if (status == EAT)
			finish_meal(phil, prog);
		else if (status == SLEEP)
			wake_up(phil, prog);
	}
	pthread_mutex_unlock(phil->fork_1);
	pthread_mutex_unlock(phil->fork_2);
	printf("PHIL: %d exit\n", phil->id);
	return (NULL);
}

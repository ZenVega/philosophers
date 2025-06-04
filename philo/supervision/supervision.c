/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervision.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 12:01:53 by uschmidt          #+#    #+#             */
/*   Updated: 2025/05/30 11:14:57 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "supervision.h"

static void	kill_phils(t_prog *prog)
{
	int		i;
	int		phil_id;

	i = -1;
	pthread_mutex_lock(prog->init_lock);
	phil_id = prog->phil_id;
	pthread_mutex_unlock(prog->init_lock);
	if (prog->n_phils == 1)
		pthread_mutex_unlock(prog->phils[0]->fork_1);
	while (++i < phil_id)
	{
		pthread_mutex_lock(prog->phils[i]->status_lock);
		prog->phils[i]->status = DEAD;
		pthread_mutex_unlock(prog->phils[i]->status_lock);
	}
}

static int	phil_died(t_prog *prog)
{
	int		i;
	int		phil_id;
	long	time;

	i = -1;
	pthread_mutex_lock(prog->init_lock);
	phil_id = prog->phil_id;
	pthread_mutex_unlock(prog->init_lock);
	while (++i < phil_id)
	{
		time = get_time();
		pthread_mutex_lock(prog->phils[i]->status_lock);
		if (prog->phils[i]->last_meal != 0
			&& prog->time_to_die < time - prog->phils[i]->last_meal)
		{
			prog->phils[i]->status = DEAD;
			pthread_mutex_unlock(prog->phils[i]->status_lock);
			log_action(prog, prog->phils[i]->id, DEAD, time);
			kill_phils(prog);
			return (1);
		}
		pthread_mutex_unlock(prog->phils[i]->status_lock);
	}
	return (0);
}

static int	dinner_done(t_prog *prog)
{
	int		i;

	i = -1;
	while (++i < prog->n_phils)
	{
		pthread_mutex_lock(prog->phils[i]->status_lock);
		if (prog->n_meals > prog->phils[i]->meals)
		{
			pthread_mutex_unlock(prog->phils[i]->status_lock);
			return (0);
		}
		pthread_mutex_unlock(prog->phils[i]->status_lock);
	}
	return (1);
}

void	*start_supervision(void *data)
{
	t_prog	*prog;

	prog = (t_prog *)data;
	while (1)
	{
		if (phil_died(prog))
			break ;
		if (prog->n_meals > 0 && dinner_done(prog))
		{
			printf("Dinner is done, %d meals eaten\n", prog->n_meals);
			kill_phils(prog);
			break ;
		}
	}
	return (NULL);
}

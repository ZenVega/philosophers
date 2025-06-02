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

static void	unlock_forks(t_prog *prog)
{
	int		i;

	i = 0;
	while (i < prog->n_phils)
		pthread_mutex_unlock(prog->forks[i++]);
}

static int	phil_died(t_prog *prog)
{
	int		i;
	long	time;

	i = -1;
	while (++i < prog->n_phils)
	{
		time = get_time();
		pthread_mutex_lock(prog->phils[i]->status_lock);
		if (prog->phils[i]->last_meal != 0
			&& prog->time_to_die < time - prog->phils[i]->last_meal)
		{
			prog->phils[i]->status = DEAD;
			pthread_mutex_unlock(prog->phils[i]->status_lock);
			pthread_mutex_lock(prog->dead_lock);
			prog->running = 0;
			pthread_mutex_unlock(prog->dead_lock);
			log_action(prog, prog->phils[i]->id, DEAD, time);
			unlock_forks(prog);
			return (1);
		}
		pthread_mutex_unlock(prog->phils[i]->status_lock);
	}
	return (0);
}

static int	dinner_done(t_prog *prog)
{
	int		i;

	i = 0;
	while (i < prog->n_phils)
	{
		pthread_mutex_lock(prog->phils[i]->status_lock);
		if (prog->n_meals > prog->phils[i]->meals)
		{
			pthread_mutex_unlock(prog->phils[i]->status_lock);
			return (1);
		}
		pthread_mutex_unlock(prog->phils[i]->status_lock);
	}
	return (0);
}
void	*start_supervision(void *data)
{
	t_prog	*prog;

	prog = (t_prog *)data;
	while (1)
	{
		if (phil_died(prog))
			break ;
		if (0 && prog->n_meals > 0 && dinner_done(prog))
		{
			printf("Dinner is done, %d meals eaten\n", prog->n_meals);
			pthread_mutex_lock(prog->dead_lock);
			prog->running = 0;
			pthread_mutex_unlock(prog->dead_lock);
			break ;
		}
	}
	return (NULL);
}

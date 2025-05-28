/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervision.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 12:01:53 by uschmidt          #+#    #+#             */
/*   Updated: 2025/03/04 14:17:23 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "supervision.h"

static void	unlock_forks(t_prog *prog)
{
	int	i;

	i = 0;
	while (i < prog->n_phils)
		pthread_mutex_unlock(&(prog->forks[i++]));
}

static int	all_alive(t_prog *prog)
{
	int		i;
	int		dead;
	long	time;
	long	time_passed;

	i = -1;
	dead = 0;
	while (++i < prog->n_phils)
	{
		time = get_time();
		pthread_mutex_lock(prog->init_lock);
		time_passed = time - prog->phils[i]->last_meal;
		pthread_mutex_unlock(prog->init_lock);
		if (prog->phils[i]->born && time_passed > prog->time_to_die)
		{
			pthread_mutex_lock(prog->init_lock);
			prog->phils[i]->status = DEAD;
			pthread_mutex_unlock(prog->init_lock);
			log_action(prog, prog->phils[i]->id, DEAD);
			unlock_forks(prog);
			pthread_mutex_lock(prog->dead_lock);
			prog->running = 0;
			pthread_mutex_unlock(prog->dead_lock);
			return (1);
		}
	}
	return (dead);
}

static int	still_eating(t_prog *prog)
{
	int	i;
	int	done;

	i = 0;
	done = 0;
	pthread_mutex_lock(prog->init_lock);
	while (!done && i < prog->n_phils)
	{
		if (prog->phils[i]->meals < prog->n_meals)
			done = 1;
		i++;
	}
	pthread_mutex_unlock(prog->init_lock);
	return (done);
}

void	*start_supervision(void *data)
{
	t_prog	*prog;

	prog = (t_prog *)data;
	while (1)
	{
		usleep(10000);
		if (all_alive(prog))
			return (NULL);
		if (prog->n_meals && !still_eating(prog))
		{
			printf("Everyone had %d meals and lives\n", prog->n_meals);
			pthread_mutex_lock(prog->dead_lock);
			prog->running = 0;
			pthread_mutex_unlock(prog->dead_lock);
			return (NULL);
		}
	}
	return (NULL);
}

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

static int	all_alive(t_phil **phils, int n_phils, long time_to_die)
{
	int		i;
	long	time;
	long	time_left;

	i = -1;
	while (++i < n_phils)
	{
		time = get_time();
		time_left = time - phils[i]->last_meal;
		printf("\nPhil: %d\nThe time is %ld\n The last meal was %ld\nThe time since the last meal was %ld\nThe time to die is %ld", phils[i]->id, time, phils[i]->last_meal, time_left, time_to_die);
		if (phils[i]->born && phils[i]->last_meal != 0 && time - phils[i]->last_meal > time_to_die)
		{
			phils[i]->alive = 0;
			return (i);
		}
	}
	return (0);
}

static int	still_eating(t_phil **phils, int n_phils, int n_meals)
{
	int	i;

	i = 0;
	while (i < n_phils)
	{
		if (phils[i]->meals < n_meals)
			return (1);
		i++;
	}
	return (0);
}

void	*start_supervision(void *data)
{
	t_prog	*prog;
	int		died;

	prog = (t_prog *)data;
	while (1)
	{
		died = all_alive(prog->phils, prog->n_phils, prog->time_to_die); 
		if (died)
		{
			printf("Philosopher %d died!\n", died);
			printf("Last meal %ld died!\n", prog->phils[died]->last_meal);
			prog->running = 0;
			break ;
		}
		if (prog->n_meals
			&& &prog->phils[prog->n_phils - 1] != (NULL)
			&& !still_eating(prog->phils, prog->n_phils, prog->n_meals))
		{
			printf("Everyone had %d meals and lives\n", prog->n_meals);
			prog->running = 0;
			break ;
		}
		usleep(5000);
	}
	return (NULL);
}

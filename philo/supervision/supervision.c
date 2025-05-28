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

static int	all_alive(t_prog *prog)
{
	int		i;
	long	time;
	long	time_passed;

	i = -1;
	while (++i < prog->n_phils)
	{
		time = get_time();
		time_passed = time - prog->phils[i]->last_meal;
		if (prog->phils[i]->born && time_passed > prog->time_to_die)
		{
			printf("\nPhil: %d DEAD\n", prog->phils[i]->id);
			prog->phils[i]->status = DEAD;
			return (1);
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
	while (prog->running == 1)
	{
		usleep(5000);
		died = all_alive(prog); 
		if (died)
		{
			prog->running = 0;
			return (NULL);
		}
		if (prog->n_meals
			&& &prog->phils[prog->n_phils - 1] != (NULL)
			&& !still_eating(prog->phils, prog->n_phils, prog->n_meals))
		{
			printf("Everyone had %d meals and lives\n", prog->n_meals);
			prog->running = 0;
			return (NULL);
		}
	}
	return (NULL);
}

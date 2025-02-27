/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:50:01 by uschmidt          #+#    #+#             */
/*   Updated: 2025/02/27 16:26:28 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_usec * 1000);
}

int	all_eaten(t_prog *prog)
{
	int	i;

	i = 0;
	while (i < prog->n_phils)
	{
		if (prog->phils[i].meals < prog->n_meals)
			return (0);
		i++;
	}
	return (1);
}

void	log_action(int phil_id, t_action act_id)
{
	char			*actions[6];

	actions[INIT] = "was born";
	actions[FORK] = "has taken fork";
	actions[EAT] = "is eating";
	actions[SLEEP] = "is sleaping";
	actions[THINK] = "is thinking";
	actions[DEAD] = "died";
	printf("%d %d %s\n", get_time(), phil_id, actions[act_id]);
}

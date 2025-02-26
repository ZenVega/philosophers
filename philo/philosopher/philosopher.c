/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:04:49 by uschmidt          #+#    #+#             */
/*   Updated: 2025/02/26 16:17:57 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	log_action(int phil_id, t_action act_id)
{
	int				timestamp;
	char			*actions[6];
	struct timeval	tv;

	actions[INIT] = "was born";
	actions[FORK] = "has taken fork";
	actions[EAT] = "is eating";
	actions[SLEEP] = "is sleaping";
	actions[THINK] = "is thinking";
	actions[DEAD] = "died";
	gettimeofday(&tv, NULL);
	timestamp = tv.tv_usec * 1000;
	printf("%d %d %s\n", timestamp, phil_id, actions[act_id]);
}

void	*create_philo(void *data)
{
	t_state	*state;
	int		id;

	state = (t_state *)data;
	id = state->phil_id++;
	log_action(id, INIT);
	return (0);
}

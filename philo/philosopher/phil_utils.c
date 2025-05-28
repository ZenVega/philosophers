/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:50:01 by uschmidt          #+#    #+#             */
/*   Updated: 2025/03/04 13:48:52 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	log_action(t_prog *prog, int phil_id, t_action act_id)
{
	char			*actions[7];
	int				running;

	actions[INIT] = "was born";
	actions[FORK] = "has taken a fork";
	actions[EAT] = "is eating";
	actions[SLEEP] = "is sleeping";
	actions[THINK] = "is thinking";
	actions[DEAD] = "died";
	pthread_mutex_lock(prog->dead_lock);
	running = prog->running;
	pthread_mutex_unlock(prog->dead_lock);
	if (running || act_id == DEAD)
		printf("%ld %d %s\n", get_time() - prog->start_time, phil_id, actions[act_id]);
}

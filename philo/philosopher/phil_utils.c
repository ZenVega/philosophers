/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:50:01 by uschmidt          #+#    #+#             */
/*   Updated: 2025/05/30 11:08:32 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	log_action(t_prog *prog, int phil_id, t_action act_id, long time)
{
	char			*actions[7];
	int				running;

	actions[INIT] = "was born";
	actions[FORK] = "has taken a fork";
	actions[EAT] = "is eating";
	actions[SLEEP] = "is sleeping";
	actions[THINK] = "is thinking";
	actions[DEAD] = "died";
	running = prog->running;
	if (running || act_id == DEAD)
		printf("%ld %d %s\n", time - prog->start_time, phil_id, actions[act_id]);
}

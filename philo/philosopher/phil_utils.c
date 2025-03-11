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

void	log_action(int phil_id, t_action act_id)
{
	char			*actions[6];

	actions[INIT] = "was born";
	actions[FORK] = "has taken fork";
	actions[EAT] = "is eating";
	actions[SLEEP] = "is sleeping";
	actions[THINK] = "is thinking";
	actions[DEAD] = "died";
	printf("%ld %d %s\n", get_time(), phil_id, actions[act_id]);
}

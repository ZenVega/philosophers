/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:35:32 by uschmidt          #+#    #+#             */
/*   Updated: 2025/02/26 14:02:56 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

int	init_state(char **argv, t_state *state)
{
	state->n_phils = ft_atoi(argv[1]);
	state->time_to_die = ft_atoi(argv[2]);
	state->time_to_eat = ft_atoi(argv[3]);
	state->time_to_sleep = ft_atoi(argv[4]);
	state->phil_id = 0;
	if (argv[5])
		state->n_meals = ft_atoi(argv[5]);
	else
		state->n_meals = 0;
	return (0);
}

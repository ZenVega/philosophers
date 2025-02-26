/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:35:12 by uschmidt          #+#    #+#             */
/*   Updated: 2025/02/26 14:03:07 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include "../utils/utils.h"

typedef struct s_state {
	int	n_phils;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	n_meals;
	int	phil_id;
}	t_state;

int	init_state(char **argv, t_state *state);

#endif

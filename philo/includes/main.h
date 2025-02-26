/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:07:33 by uschmidt          #+#    #+#             */
/*   Updated: 2025/02/26 15:09:29 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "constants.h"

typedef struct s_state {
	int	n_phils;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	n_meals;
	int	phil_id;
}	t_state;
#endif

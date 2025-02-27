/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:09:46 by uschmidt          #+#    #+#             */
/*   Updated: 2025/02/27 16:27:35 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

# include "main.h"

typedef enum e_action {
	INIT = 0,
	FORK = 1,
	EAT = 2,
	SLEEP = 3,
	THINK = 4,
	DEAD = 5,
}	t_action;

typedef struct s_phil {
	int				id;
	int				alive;
	t_action		status;
	int				last_meal;
	int				last_nap;
	pthread_mutex_t	fork_1;
	pthread_mutex_t	fork_2;
	int				meals;
}	t_phil;

typedef struct s_prog {
	int				n_phils;
	pthread_t		*tids;
	pthread_mutex_t	*forks;
	pthread_mutex_t	init_lock;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_meals;
	int				phil_id;
	t_phil			*phils;
}	t_prog;
#endif

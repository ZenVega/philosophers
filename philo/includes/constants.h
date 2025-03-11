/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:09:46 by uschmidt          #+#    #+#             */
/*   Updated: 2025/03/04 13:27:32 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

# include <pthread.h>

typedef enum e_action {
	INIT = 0,
	FORK = 1,
	EAT = 2,
	SLEEP = 3,
	THINK = 4,
	DEAD = 5,
}	t_action;

typedef enum e_app_state {
	BEFORE_INIT = 0,
	PROG_INIT = 1,
	THREAD_INIT = 2,
	FORK_INIT = 3,
	PHIL_INIT = 4,
	SUPER_INIT = 5,
}	t_app_state;

typedef struct s_phil {
	int				id;
	int				alive;
	int				born;
	t_action		status;
	long			last_meal;
	long			last_nap;
	pthread_mutex_t	fork_1;
	pthread_mutex_t	fork_2;
	int				meals;
}	t_phil;

typedef struct s_prog {
	int				n_phils;
	pthread_t		*tids;
	pthread_mutex_t	**forks;
	pthread_mutex_t	*init_lock;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_meals;
	int				phil_id;
	t_phil			*phils;
	int				running;
}	t_prog;
#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:05:07 by uschmidt          #+#    #+#             */
/*   Updated: 2025/02/27 12:24:34 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include "../includes/main.h"
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

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
}	t_phil;

void	*create_phil(void *data);
int		get_time(void);
void	log_action(int phil_id, t_action act_id);
#endif

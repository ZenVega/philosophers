/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:05:07 by uschmidt          #+#    #+#             */
/*   Updated: 2025/02/26 16:27:25 by uschmidt         ###   ########.fr       */
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

void	*create_philo(void *data);
#endif

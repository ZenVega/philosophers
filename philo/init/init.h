/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:35:12 by uschmidt          #+#    #+#             */
/*   Updated: 2025/02/26 15:27:56 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include <pthread.h>
# include <stdlib.h>
# include "../includes/main.h"
# include "../utils/utils.h"

int	init_thread_ids(int n_phils, pthread_t **tid);
int	init_state(char **argv, t_state *state);
int	init_forks(int philos, pthread_mutex_t **forks);

#endif

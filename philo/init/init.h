/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:35:12 by uschmidt          #+#    #+#             */
/*   Updated: 2025/03/04 12:38:50 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include <pthread.h>
# include <stdlib.h>
# include "../includes/constants.h"
# include "../utils/utils.h"
# include "../philosopher/philosopher.h"

int		init_threads(int n_phils, pthread_t **tid, t_prog *prog);
int		init_prog(char **argv, t_prog *prog);
int		init_forks(int n_phils, pthread_mutex_t ***forks,
			pthread_mutex_t **init_lock);
void	init_phils(t_prog *prog);

#endif

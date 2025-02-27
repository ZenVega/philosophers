/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:05:07 by uschmidt          #+#    #+#             */
/*   Updated: 2025/02/27 16:26:36 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include "../includes/constants.h"
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

void	*create_phil(void *data);
int		get_time(void);
void	log_action(int phil_id, t_action act_id);
int		all_eaten(t_prog *prog);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:05:07 by uschmidt          #+#    #+#             */
/*   Updated: 2025/05/30 11:08:46 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include "../includes/constants.h"
# include "../utils/utils.h"
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>

void	*create_phil(void *data);
void	log_action(t_prog *prog, int phil_id, t_action act_id, long time);
int		is_dead(t_phil *phil);
void	upadate_meal(t_phil *phil);

#endif

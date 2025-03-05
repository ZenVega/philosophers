/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:05:07 by uschmidt          #+#    #+#             */
/*   Updated: 2025/03/04 13:51:30 by uschmidt         ###   ########.fr       */
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
void	log_action(int phil_id, t_action act_id);

#endif

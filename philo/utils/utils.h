/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:02:38 by uschmidt          #+#    #+#             */
/*   Updated: 2025/02/27 16:25:51 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef UTILS_H
# define UTILS_H
# include <string.h>
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include "../includes/constants.h"

int		ft_atoi(const char *nptr);
int		on_error(int err, t_prog state);
void	clean_up(t_prog state);

#endif

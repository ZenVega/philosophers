/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 10:44:13 by uschmidt          #+#    #+#             */
/*   Updated: 2025/05/30 10:44:58 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	on_error(int err, t_prog prog, t_app_state state)
{
	errno = err;
	clean_up(prog, state);
	printf("Error: %s\n", strerror(errno));
	return (errno);
}

int	is_arg_valid(char **argv)
{
	int		i;
	char	*argv_curr;

	i = 0;
	argv++;
	while (*argv)
	{
		argv_curr = *argv;
		while (argv_curr[i])
		{
			if (!(argv_curr[i] >= '0' && argv_curr[i] <= '9'))
				return (0);
			i++;
		}
		argv++;
		i = 0;
	}
	return (1);
}

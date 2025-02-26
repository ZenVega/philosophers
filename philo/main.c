/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:12:07 by uschmidt          #+#    #+#             */
/*   Updated: 2025/02/26 14:01:53 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <unistd.h>
#include "init/init.h"
#include "utils/utils.h"

void	*create_philo(void *data)
{
	t_state	*state;
	int		id;

	state = (t_state *)data;
	id = state->phil_id++;
	printf("I'm philly no: %d\n", id);
	return (0);
}

int	main(int argc, char **argv)
{
	pthread_t			tid;
	static t_state		state;
	int					err;
	int					i;

	if (argc < 5 || argc > 6)
		return (on_error(EINVAL));
	err = init_state(argv, &state);
	if (err)
		return (on_error(err));
	i = 0;
	while (i++ < state.n_phils)
	{
		pthread_create(&tid, NULL, create_philo, &state);
		pthread_join(tid, NULL);
	}
	pthread_exit(NULL); 
}

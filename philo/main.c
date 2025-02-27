/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:12:07 by uschmidt          #+#    #+#             */
/*   Updated: 2025/02/26 15:30:39 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "init/init.h"
#include "utils/utils.h"
#include "philosopher/philosopher.h"

int	main(int argc, char **argv)
{
	static t_state		state;
	int					err;
	int					i;

	if (argc < 5 || argc > 6)
		return (on_error(EINVAL));
	err = init_state(argv, &state);
	if (err)
		return (on_error(err));
	err = get_thread_ids(state.n_phils, &state.tids);
	i = 0;
	while (i < state.n_phils)
		pthread_create(&state.tids[i++], NULL, create_philo, &state);
	i = 0;
	while (i < state.n_phils)
		pthread_join(state.tids[i++], NULL);
	pthread_exit(NULL);
	free(state.tids);
}

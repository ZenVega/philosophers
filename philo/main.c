/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:12:07 by uschmidt          #+#    #+#             */
/*   Updated: 2025/03/04 14:23:15 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/main.h"

//TODO: How to implement a rotating system?
int	main(int argc, char **argv)
{
	static t_prog		prog;
	int					err;
	int					i;
	pthread_t			super_id;

	if (argc < 5 || argc > 6)
		return (on_error(EINVAL, prog));
	err = init_prog(argv, &prog);
	if (err)
		return (on_error(err, prog));
	err = init_threads(prog.n_phils, &prog.tids, &prog);
	if (err)
		return (on_error(err, prog));
	err = init_forks(prog.n_phils, &prog.forks, &prog.init_lock);
	if (err)
		return (on_error(err, prog));
	init_phils(&prog);
	i = 0;
	while (i < prog.n_phils)
		pthread_create(&prog.tids[i++], NULL, create_phil, &prog);
	pthread_create(&super_id, NULL, start_supervision, &prog);
	i = 0;
	pthread_join(super_id, NULL);
	while (i < prog.n_phils)
		pthread_join(prog.tids[i++], NULL);
	clean_up(prog);
	return (0);
}

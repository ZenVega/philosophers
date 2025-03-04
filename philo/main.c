/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:12:07 by uschmidt          #+#    #+#             */
/*   Updated: 2025/02/27 16:25:27 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init/init.h"
#include "utils/utils.h"
#include "philosopher/philosopher.h"

int	main(int argc, char **argv)
{
	static t_prog		prog;
	int					err;
	int					i;

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
		pthread_create(&prog.tids[i], NULL, create_phil, &prog);
	i = 0;
	while (i < prog.n_phils)
		pthread_join(prog.tids[i++], NULL);
	clean_up(prog);
}

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

static int	init(int argc, char **argv, t_prog *prog)
{
	int					err;

	if (argc < 5 || argc > 6 || !is_arg_valid(argv))
		return (on_error(EINVAL, *prog, BEFORE_INIT));
	err = init_prog(argv, prog);
	if (err)
		return (on_error(err, *prog, BEFORE_INIT));
	err = init_threads((*prog).n_phils, prog);
	if (err)
		return (on_error(err, *prog, PROG_INIT));
	err = init_mutexes(prog);
	if (err)
		return (on_error(err, *prog, THREAD_INIT));
	err = init_phils(prog);
	if (err)
		return (on_error(err, *prog, THREAD_INIT));
	return (0);
}

int	main(int argc, char **argv)
{
	t_prog	*prog;
	int		i;

	prog = (t_prog *)malloc(sizeof(t_prog));
	if (init(argc, argv, prog))
		return (free(prog), 1);
	i = 0;
	while (i < prog->n_phils)
		pthread_create(&(prog->tids[i++]), NULL, create_phil, prog);
	pthread_create(&(prog->super_id), NULL, start_supervision, prog);
	pthread_join(prog->super_id, NULL);
	i = 0;
	while (i < prog->n_phils)
		pthread_join(prog->tids[i++], NULL);
	clean_mutexes(*prog);
	clean_up(*prog, SUPER_INIT);
	free(prog);
	return (i);
}

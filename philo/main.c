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
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "init/init.h"

int	on_error(int err)
{
	errno = err;
	printf("Error: %s\n", strerror(errno));
	return (errno);
}

void	*callback(void *data)
{
	if (*(int *)data == 1)
		write(1, "hello thread", 12);
	return (0);
}

int	main(int argc, char **argv)
{
	pthread_t		tid;
	static t_state	*state;
	int				err;

	if (argc < 5 || argc > 6)
		return (on_error(EINVAL));
	err = init_state(argv, state);
	if (err)
		return (on_error(err));
	if (argv && argc == 1)
	{
		pthread_create(&tid, NULL, callback, &state.n_phils);
		pthread_join(tid, NULL);
	}
	pthread_exit(NULL); 
}

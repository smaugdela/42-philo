/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 13:32:14 by smagdela          #+#    #+#             */
/*   Updated: 2022/01/04 13:45:09 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	*table_ronde;

	if (check_args(argc, argv) == FALSE)
		return (42);
	table_ronde = init_table(argv);
	if (table_ronde == NULL)
		return (42);
	printf("philos = %lu\ndie = %lu\neat = %lu\nsleep = %lu\nfull = %lu\n",
		table_ronde->philos, table_ronde->tt_die, table_ronde->tt_eat,
		table_ronde->tt_sleep, table_ronde->full);
	return (destroyer(table_ronde));
}

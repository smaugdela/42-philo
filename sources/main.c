/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 13:32:14 by smagdela          #+#    #+#             */
/*   Updated: 2022/01/05 12:55:20 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	wait_end(t_data table)
{
	while(table.death == FALSE && table.nb_philos_full < table.nb_philos)
	{
	}
	if (table.death == TRUE)
		return (DEAD);
	else if (table.nb_philos_full == table.nb_philos)
		return (FULL);
	else
		return (42);
}

int	main(int argc, char **argv)
{
	t_data	table;
	t_philo	*philos;
	int		ret;

	if (check_args(argc, argv) == FALSE)
		return (42);
	if (init_table(argv, &table) == FALSE)
		return (42);
	philos = (t_philo *)malloc(sizeof(t_philo) * table.nb_philos);
	if (philos == NULL)
		return (42);
	if (init_philos(philos, &table) == FALSE)
	{
		free(philos);
		return (42);
	}
	if (launch(philos) == FALSE)
	{
		free(philos);
		return (42);
	}
	ret = wait_end(table);
	free(philos);
	return (0);
}

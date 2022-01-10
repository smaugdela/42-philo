/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 13:32:14 by smagdela          #+#    #+#             */
/*   Updated: 2022/01/10 12:22:40 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	wait_end(t_philo *philos)
{
	size_t	i;

	i = 0;
	while(philos->table->death == FALSE &&
		philos->table->nb_philos_full < philos->table->nb_philos)
	{
	}
	while (i < philos->table->nb_philos)
	{
		pthread_join(philos[i].thread_id, NULL);
		++i;
	}
	if (philos->table->death == TRUE)
		return (DEAD);
	else if (philos->table->nb_philos_full == philos->table->nb_philos)
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
	ret = wait_end(philos);
	free(philos);
	return (ret);
}

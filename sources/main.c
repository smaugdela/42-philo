/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 13:32:14 by smagdela          #+#    #+#             */
/*   Updated: 2022/01/10 19:49:40 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	wait_end(t_philo *philos)
{
	size_t	i;

	pthread_mutex_lock(&philos->table->death_lock);
	pthread_mutex_lock(&philos->table->full_lock);
	while(philos->table->death == FALSE &&
		philos->table->nb_philos_full < philos->table->nb_philos)
	{
		pthread_mutex_unlock(&philos->table->full_lock);
		pthread_mutex_unlock(&philos->table->death_lock);
		usleep(500);
		pthread_mutex_lock(&philos->table->full_lock);
		pthread_mutex_lock(&philos->table->death_lock);
	}
	pthread_mutex_unlock(&philos->table->full_lock);
	pthread_mutex_unlock(&philos->table->death_lock);
	i = 0;
	while (i < philos->table->nb_philos)
	{
		pthread_join(philos[i].thread_id, NULL);
		++i;
	}
	if (philos->table->death == TRUE)
	{
		free(philos);
		return (DEAD);
	}
	else if (philos->table->nb_philos_full == philos->table->nb_philos)
	{
		printf("%6lu ms:      Philosophers are full!\n",
		ft_clock() - philos->table->clock_start);
		free(philos);
		return (FULL);
	}
	free(philos);
	return (42);
}

int	main(int argc, char **argv)
{
	t_data	table;
	t_philo	*philos;

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
	return (wait_end(philos));
}

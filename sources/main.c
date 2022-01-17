/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 13:32:14 by smagdela          #+#    #+#             */
/*   Updated: 2022/01/17 17:51:12 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	clean(t_philo *philos, t_data *table)
{
	size_t	i;

	if (philos != NULL)
	{
		i = 0;
		while (i < philos->table->nb_philos)
		{
			pthread_mutex_destroy(&philos[i].left_fork);
			pthread_mutex_destroy(&philos[i].state_lock);
			++i;
		}
		free(philos);
	}
	if (table != NULL)
	{
		pthread_mutex_destroy(&table->clock_lock);
		pthread_mutex_destroy(&table->talk_lock);
		pthread_mutex_destroy(&table->death_lock);
		pthread_mutex_destroy(&table->full_lock);
	}
	return (1);
}

static void	vulture(t_philo *philos)
{
	while (42)
	{
		pthread_mutex_lock(&philos->table->death_lock);
		pthread_mutex_lock(&philos->table->full_lock);
		if (philos->table->death == FALSE
			&& philos->table->nb_philos_full < philos->table->nb_philos)
			break ;
		pthread_mutex_unlock(&philos->table->death_lock);
		pthread_mutex_unlock(&philos->table->full_lock);
		usleep(500);
	}
	pthread_mutex_unlock(&philos->table->death_lock);
	pthread_mutex_unlock(&philos->table->full_lock);
}

static int	wait_end(t_philo *philos)
{
	size_t	i;

	vulture(philos);
	i = 0;
	while (i < philos->table->nb_philos)
	{
		pthread_join(philos[i].thread_id, NULL);
		++i;
	}
	if (philos->table->death == TRUE)
		return (DEAD * clean(philos, philos->table));
	else if (philos->table->nb_philos_full == philos->table->nb_philos)
		return (0 * clean(philos, philos->table));
	return (42 * clean(philos, philos->table));
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
		return (42 * clean(NULL, &table));
	if (init_philos(philos, &table) == FALSE)
		return (42 * clean(philos, &table));
	if (launch(philos) == FALSE)
		return (42 * clean(philos, &table));
	return (wait_end(philos));
}

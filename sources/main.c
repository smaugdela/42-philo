/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 13:32:14 by smagdela          #+#    #+#             */
/*   Updated: 2022/01/24 20:08:47 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	clean(t_philo *philos, t_data *table)
{
	size_t	i;

	pthread_mutex_destroy(&table->clock_lock);
	pthread_mutex_destroy(&table->talk_lock);
	pthread_mutex_destroy(&table->death_lock);
	pthread_mutex_destroy(&table->full_lock);
	if (philos != NULL)
	{
		i = 0;
		while (i < table->nb_philos && &philos[i] != NULL)
		{
			if (philos[i].left_fork != NULL)
			{
				pthread_mutex_destroy(philos[i].left_fork);
				free(philos[i].left_fork);
			}
			if (philos[i].state_lock != NULL)
			{
				pthread_mutex_destroy(philos[i].state_lock);
				free(philos[i].state_lock);
			}
			++i;
		}
		free(philos);
	}
	return (1);
}

static t_bool	vulture(t_philo *philos)
{
	size_t	i;

	i = 0;
	while (i < philos->table->nb_philos)
	{
		pthread_mutex_lock(&philos->table->clock_lock);
		pthread_mutex_lock(philos[i].state_lock);
		pthread_mutex_lock(&philos->table->full_lock);
		if (ft_clock() - philos[i].last_meal >= philos->table->tt_die)
		{
			pthread_mutex_unlock(&philos->table->clock_lock);
			philos[i].state = DEAD;
			pthread_mutex_unlock(philos[i].state_lock);
			pthread_mutex_unlock(&philos->table->full_lock);
			printf("Burying\n");
			return (DEAD);
		}
		else if (philos[i].state == TERM)
			philos->table->nb_philos_full += 1;
		if (philos->table->nb_philos_full >= philos->table->nb_philos)
		{
			pthread_mutex_unlock(&philos->table->full_lock);
			pthread_mutex_unlock(philos[i].state_lock);
			printf("Terminating\n");
			return (TERM);
		}
		pthread_mutex_unlock(&philos->table->clock_lock);
		pthread_mutex_unlock(philos[i].state_lock);
		pthread_mutex_unlock(&philos->table->full_lock);
		++i;
	}
	return (ALIVE);
}

static int	wait_end(t_philo *philos)
{
	size_t	i;

	while (vulture(philos) == ALIVE)
		usleep(250);
	i = 0;
	while (i < philos->table->nb_philos)
	{
		pthread_mutex_lock(philos[i].state_lock);
		if (philos[i].state != DEAD)
			philos[i].state = TERM;
		else
		{
			pthread_mutex_lock(&philos->table->death_lock);
			philos->table->death = TRUE;
			pthread_mutex_unlock(&philos->table->death_lock);
		}
		pthread_mutex_unlock(philos[i].state_lock);
		++i;
	}
	i = 0;
	while (i < philos->table->nb_philos)
	{
		pthread_join(philos[i].thread_id, NULL);
		printf("Joined %lu\n", i + 1);
		++i;
	}
	printf("Cleaning\n");
	if (philos->table->death == TRUE
		|| philos->table->nb_philos_full >= philos->table->nb_philos)
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

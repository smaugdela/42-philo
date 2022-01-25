/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 13:32:14 by smagdela          #+#    #+#             */
/*   Updated: 2022/01/25 17:09:27 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	check_philo(t_philo	*philo)
{
	if (philo->state == TERM)
		philo->table->nb_philos_full += 1;
	else if (ft_clock() - philo->last_meal >= philo->table->tt_die)
	{
		philo->state = DEAD;
		return (DEAD);
	}
	if (philo->table->nb_philos_full >= philo->table->nb_philos)
		return (TERM);
	return (ALIVE);
}

static t_bool	vulture(t_philo *philos)
{
	size_t	i;
	t_bool	ret;

	ret = ALIVE;
	i = 0;
	pthread_mutex_lock(&philos->table->clock_lock);
	pthread_mutex_lock(&philos->table->full_lock);
	while (i < philos->table->nb_philos)
	{
		pthread_mutex_lock(philos[i].state_lock);
		ret = check_philo(&philos[i]);
		pthread_mutex_unlock(philos[i].state_lock);
		if (ret != ALIVE)
			break ;
		++i;
	}
	pthread_mutex_unlock(&philos->table->clock_lock);
	pthread_mutex_unlock(&philos->table->full_lock);
	return (ret);
}

static int	wait_end(t_philo *philos)
{
	size_t	i;

	while (vulture(philos) == ALIVE)
		usleep(500);
	i = 0;
	while (i < philos->table->nb_philos)
	{
		pthread_mutex_lock(philos[i].state_lock);
		if (philos[i].state == ALIVE)
			philos[i].state = TERM;
		pthread_mutex_unlock(philos[i].state_lock);
		++i;
	}
	i = 0;
	while (i < philos->table->nb_philos)
	{
		pthread_join(philos[i].thread_id, NULL);
		++i;
	}
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 16:38:09 by smagdela          #+#    #+#             */
/*   Updated: 2022/01/04 13:44:44 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	usage(const char *str)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\nUsage: ./philo <number_of_philosophers> ", 2);
	ft_putstr_fd("<time_to_die> <time_to_eat> <time_to_sleep> ", 2);
	ft_putstr_fd("[(optional) number_of_times_each_philosopher_must_eat]\n", 2);
	return (FALSE);
}

t_bool	check_args(int argc, char **argv)
{
	int	index;

	if (argc < 5 || argc > 6)
		return (usage("Bad argument number"));
	index = 1;
	while (argv[index] != NULL)
	{
		if (ft_is_str_digits(argv[index]) == FALSE
			|| ft_checkposint(argv[index]) == FALSE)
			return (usage("Bad argument type (only positive integers)"));
		++index;
	}
	return (TRUE);
}

static t_bool	init_mutexes(t_table *table)
{
	pthread_mutex_t	lock_1;
	pthread_mutex_t	lock_2;

	if (pthread_mutex_init(&lock_1, NULL) != 0)
		return (FALSE);
	if (pthread_mutex_init(&lock_2, NULL) != 0)
	{
		pthread_mutex_destroy(&lock_1);
		return (FALSE);
	}
	table->fork_lock = lock_1;
	table->talk_lock = lock_2;
	return (TRUE);
}

static t_bool	init_forks(t_table *table)
{
	table->forks = (t_bool *)malloc(sizeof(t_bool) * table->philos);
	if (table->forks == NULL)
	{
		pthread_mutex_destroy(&(table->fork_lock));
		pthread_mutex_destroy(&(table->talk_lock));
		free(table);
		return (FALSE);
	}
	return (TRUE);
}

t_table	*init_table(char **argv)
{
	t_table	*table;

	table = (t_table *)malloc(sizeof(t_table));
	if (table == NULL)
		return (NULL);
	table->philos = ft_atoi(argv[1]);
	table->tt_die = ft_atoi(argv[2]);
	table->tt_eat = ft_atoi(argv[3]);
	table->tt_sleep = ft_atoi(argv[4]);
	if (argv[5] != NULL)
		table->full = ft_atoi(argv[5]);
	else
		table->full = 0;
	table->death = FALSE;
	if (init_mutexes(table) == FALSE)
	{
		free(table);
		return (NULL);
	}
	if (init_forks(table) == FALSE)
		return (NULL);
	return (table);
}

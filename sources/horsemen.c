/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horsemen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 13:17:51 by smagdela          #+#    #+#             */
/*   Updated: 2022/01/04 17:09:59 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*faucheuse(size_t index, t_table *table)
{
	void	*last_breath;
	t_philo	*tmp;

	if (table->death == FALSE)
		table->death = TRUE;
	pthread_join(table->philos[index - 1], &last_breath);
	tmp = (t_philo *)last_breath;
	printf("Death:	I took philosopher number %lu.\n", tmp->index);
	return (last_breath);
}

int	destroyer(t_table *table)
{
	pthread_mutex_destroy(&(table->fork_lock));
	pthread_mutex_destroy(&(table->talk_lock));
	free(table->forks);
	free(table->philos);
	free(table);
	return (0);
}

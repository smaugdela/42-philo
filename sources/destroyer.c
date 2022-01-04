/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroyer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 13:17:51 by smagdela          #+#    #+#             */
/*   Updated: 2022/01/04 13:45:41 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	destroyer(t_table *table)
{
	pthread_mutex_destroy(&(table->fork_lock));
	pthread_mutex_destroy(&(table->talk_lock));
	free(table->forks);
	free(table);
	return (0);
}

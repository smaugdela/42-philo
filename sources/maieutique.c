/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maieutique.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 13:53:55 by smagdela          #+#    #+#             */
/*   Updated: 2022/01/04 17:11:08 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	philo_birth(int	index, t_table *table)
{
	pthread_t	philo;
	t_philo		info;

	info.index = index;
	info.table = table;
	if (pthread_create(&philo, NULL, &ft_philo, &info) != 0)
	{
		table->death = TRUE;
		return (FALSE);
	}
	table->philos[index - 1] = philo;
	return (TRUE);
}

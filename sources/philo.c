/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 16:38:35 by smagdela          #+#    #+#             */
/*   Updated: 2022/01/04 17:10:37 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_philo(void *id)
{
	t_philo	info;

	info = *(t_philo *)id;
	pthread_mutex_lock(&(info.table->talk_lock));
	ft_blabla(info, "I'm Alive!\n");
	pthread_mutex_unlock(&(info.table->talk_lock));
	while (ft_clock() < (int)(info.index) * 1000)
	{
	}
	if (info.table->death == FALSE)
	{
		pthread_mutex_lock(&(info.table->talk_lock));
		ft_blabla(info, "Farewell cruel world! *Commits suicide*\n");
		pthread_mutex_unlock(&(info.table->talk_lock));
		info.table->death = TRUE;
	}
	else
	{
		pthread_mutex_lock(&(info.table->talk_lock));
		ft_blabla(info, "F*** you Socrate! NOOOOO!!!\n");
		pthread_mutex_unlock(&(info.table->talk_lock));
	}
	return (id);
}

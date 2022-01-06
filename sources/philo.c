/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 16:38:35 by smagdela          #+#    #+#             */
/*   Updated: 2022/01/06 13:11:42 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*faucheuse(void *info)
{
	t_philo		*philo;
	int			memento_mori;

	philo = (t_philo *)info;
	memento_mori = philo->nb_meals;
	usleep(philo->table->tt_die);
	if (philo->nb_meals == memento_mori)
	{
		philo->state = DEAD;
		pthread_mutex_lock(&philo->table->death_lock);
		philo->table->death = TRUE;
		pthread_mutex_unlock(&philo->table->death_lock);
	}
	return (NULL);
}

void	*ft_philo(void *info)
{
	t_philo	*philo;

	philo = (t_philo *)info;
	pthread_create(philo->faucheuse_id, NULL, &faucheuse, philo);
	while (philo->state == ALIVE)
	{
		pthread_mutex_lock(&philo->left_fork);
		pthread_mutex_lock(&philo->table->talk_lock);
		ft_blabla(philo->index, "has taken left fork.");
		pthread_mutex_unlock(&philo->table->talk_lock);
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(&philo->table->talk_lock);
		ft_blabla(philo->index, "has taken right fork.");
		pthread_mutex_unlock(&philo->table->talk_lock);
		pthread_mutex_lock(&philo->table->talk_lock);
		ft_blabla(philo->index, "is eating.");
		pthread_mutex_unlock(&philo->table->talk_lock);
		pthread_detach(philo->faucheuse_id);
		pthread_create(philo->faucheuse_id, NULL, &faucheuse, philo);
		philo->nb_meals += 1;
		pthread_mutex_lock(&philo->table->talk_lock);
		ft_blabla(philo->index, "is sleeping.");
		pthread_mutex_unlock(&philo->table->talk_lock);
		pthread_mutex_unlock(&philo->left_fork);
		pthread_mutex_unlock(&philo->right_fork);
		pthread_mutex_lock(&philo->table->talk_lock);
		ft_blabla(philo->index, "is thinking.");
		pthread_mutex_unlock(&philo->table->talk_lock);
	}
	return (philo);
}

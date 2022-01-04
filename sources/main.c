/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 13:32:14 by smagdela          #+#    #+#             */
/*   Updated: 2022/01/04 16:50:26 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	*table_ronde;
	size_t	i;

	if (check_args(argc, argv) == FALSE)
		return (42);
	table_ronde = init_table(argv);
	if (table_ronde == NULL)
		return (42);
	i = 0;
	ft_clock();
	while (++i <= table_ronde->nb_philos)
	{
		if (philo_birth(i, table_ronde) == FALSE)
			break ;
	}
	while (table_ronde->death == FALSE)
	{
	}
	i = 0;
	while (++i <= table_ronde->nb_philos)
		faucheuse(i, table_ronde);
	return (destroyer(table_ronde));
}

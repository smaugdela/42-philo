/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 13:07:05 by smagdela          #+#    #+#             */
/*   Updated: 2022/01/04 13:07:47 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	ft_checkposint(char *nb)
{
	char	*int_extremum;
	int		i;

	int_extremum = "2147483647";
	if (nb[0] == '-' || ft_strlen(nb) > ft_strlen(int_extremum))
		return (FALSE);
	else if (ft_strlen(nb) == ft_strlen(int_extremum))
	{
		i = 0;
		while (nb[i])
		{
			if (nb[i] > int_extremum[i] || !ft_isdigit(nb[i]))
				return (FALSE);
			++i;
		}
		return (TRUE);
	}
	else
		return (TRUE);
}

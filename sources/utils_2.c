/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 13:07:05 by smagdela          #+#    #+#             */
/*   Updated: 2022/01/04 16:29:02 by smagdela         ###   ########.fr       */
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

int		ft_clock(void)
{
	static int	start = 0;
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	if (start == 0)
		start = (tv.tv_usec / 1000) + (tv.tv_sec * 1000);
	return ((tv.tv_usec /1000) + (tv.tv_sec * 1000) - start);
}

void	ft_blabla(t_philo info, const char *str)
{	
	printf("%-10d %4lu %s", ft_clock(), info.index, str);
}
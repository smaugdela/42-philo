/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 13:32:12 by smagdela          #+#    #+#             */
/*   Updated: 2022/01/03 17:18:29 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdint.h>

/* Boolean type definition */
typedef uint8_t t_bool;
# define TRUE 1
# define FALSE 0

typedef struct	s_table{
	size_t			philos;
	t_bool			*forks;
	size_t			tt_die;
	size_t			tt_eat;
	size_t			tt_sleep;
	size_t			full;
	t_bool			death;
	pthread_mutex_t	fork_lock;
	pthread_mutex_t	talk_lock;
}	t_table;

void	ft_putstr_fd(const char *str, int fd);
t_bool	ft_is_str_digits(const char* str);
t_bool  check_args(int argc, char **argv);
int		ft_isdigit(int c);
int		ft_atoi(const char *str);
t_table	*init_table(char **argv);

#endif

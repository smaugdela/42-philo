/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 13:32:12 by smagdela          #+#    #+#             */
/*   Updated: 2022/01/04 17:11:06 by smagdela         ###   ########.fr       */
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
typedef uint8_t	t_bool;
# define TRUE 1
# define FALSE 0

typedef struct s_table
{
	size_t			nb_philos;
	pthread_t		*philos;
	t_bool			*forks;
	size_t			tt_die;
	size_t			tt_eat;
	size_t			tt_sleep;
	size_t			full;
	t_bool			death;
	pthread_mutex_t	fork_lock;
	pthread_mutex_t	talk_lock;
}	t_table;

typedef struct s_philo
{
	size_t	index;
	t_table	*table;
}	t_philo;

/* Utilities Functions */
void	ft_putstr_fd(const char *str, int fd);
size_t	ft_strlen(const char *str);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
t_bool	ft_is_str_digits(const char *str);
t_bool	ft_checkposint(char *nb);

t_bool	check_args(int argc, char **argv);
t_table	*init_table(char **argv);

void	*faucheuse(size_t index, t_table *table);
int		destroyer(t_table *table);

t_bool	philo_birth(int	index, t_table *table);
void	*ft_philo(void *table);

int		ft_clock(void);
void	ft_blabla(t_philo info, const char *str);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 13:32:12 by smagdela          #+#    #+#             */
/*   Updated: 2022/01/05 12:48:49 by smagdela         ###   ########.fr       */
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

# define ALIVE 0
# define FULL 1
# define DEAD 2

typedef struct s_data
{
	size_t			nb_philos;
	size_t			nb_philos_full;
	size_t			tt_die;
	size_t			tt_eat;
	size_t			tt_sleep;
	int				full;
	t_bool			death;
	uint64_t		clock_start;
	pthread_mutex_t	talk_lock;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	full_lock;
}	t_data;

typedef struct s_philo
{
	size_t			index;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*table;
	int				nb_meals;
	t_bool			state;
}	t_philo;

/* Utilities Functions */
void			ft_putstr_fd(const char *str, int fd);
size_t			ft_strlen(const char *str);
int				ft_atoi(const char *str);
int				ft_isdigit(int c);
t_bool			ft_is_str_digits(const char *str);
t_bool			ft_checkposint(char *nb);
uint64_t		ft_clock(void);

/* Parsing */
t_bool	check_args(int argc, char **argv);
t_bool	init_table(char **argv, t_data *table);
t_bool	init_philos(t_philo *philos, t_data *table);

/* Execution */
t_bool	launch(t_philo *philos);
void	*ft_philo(void *table);

void	*faucheuse(size_t index, t_table *table);
int		destroyer(t_table *table); 


//void	ft_blabla(t_philo info, const char *str);

#endif

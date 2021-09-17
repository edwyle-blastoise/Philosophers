/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblastoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 19:05:04 by eblastoi          #+#    #+#             */
/*   Updated: 2021/09/17 19:05:06 by eblastoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_data {
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				full_philo;
	pthread_mutex_t	print_message;
	unsigned long	start_philo;
}				t_data;

typedef struct s_philo {
	t_data			*data;
	int				id;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	philo_meal;
	pthread_t		thread;
	int				times_of_eating;
	unsigned long	last_meal;
}				t_philo;

void			*life_cycle(void *philo);
unsigned long	get_time(void);
int				ft_atoi(char *str);
int				ft_isdigit(int c);
void			print_status(t_philo *philo, int status);
void			ft_usleep(useconds_t time);
void			free_all(t_data *data, t_philo *philo);

#endif

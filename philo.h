#ifndef PHILO_H
# define PHILO_H

#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h> //?
#include <stdio.h>
#include <sys/time.h>

typedef struct	s_data {
	int			number_of_philosophers;
	unsigned long long time_to_die;
	unsigned long long time_to_eat;
	unsigned long long time_to_sleep;
	int			number_of_times_each_philosopher_must_eat;
	int			full_philo;
	pthread_mutex_t		print_message;
	pthread_mutex_t		death;
	pthread_mutex_t		**forks;
	int				flag_death;
}				t_data;

typedef struct		s_philosopher {
	t_data			*data;
	int				id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				times_of_eating;
	unsigned long long	start_philo;
	unsigned long long	last_meal;
}					t_philosopher;

void*			life_cycle(void *philo);
unsigned long long  get_time(void);
int				ft_atoi(char *str);
int				ft_isdigit(int c);
void			print_status(t_philosopher *philosopher, int status);
void			ft_usleep(useconds_t time);
int				destroy_mutex_forks(t_data *data);
void			free_all(t_data *data, t_philosopher	*philosophers, pthread_t *threads);

#endif
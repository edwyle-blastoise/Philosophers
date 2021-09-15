#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_data {
	int					num_of_philo;
	unsigned long long	time_to_die;
	unsigned long long	time_to_eat;
	unsigned long long	time_to_sleep;
	int					must_eat;
	int					flag_death;
	int					full_philo;
	pthread_mutex_t		print_message;
	pthread_mutex_t		death;
	pthread_mutex_t		**forks;
}				t_data;

typedef struct s_philo {
	t_data				*data;
	int					id;
	int					times_of_eating;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	unsigned long long	start_philo;
	unsigned long long	last_meal;
}					t_philo;

void				*life_cycle(void *philosopher);
int					ft_atoi(char *str);
int					ft_isdigit(int c);
unsigned long long	get_time(void);
void				ft_usleep(useconds_t time);
void				print_status(t_philo *philo, int status);
int					destroy_mutex_forks(t_data *data);
void				free_all(t_data *data, t_philo *philo, pthread_t *threads);

#endif
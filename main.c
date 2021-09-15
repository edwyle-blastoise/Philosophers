#include "philo.h"

void	check_death(t_philo *philo)
{
	if ((get_time() - philo->last_meal) > philo->data->time_to_die)
	{
		philo->data->flag_death = 1;
		print_status(philo, 1);
		pthread_mutex_lock(&philo->data->death);
	}
}

void	check_philo(t_philo *philo)
{
	int	i;

	while (!philo->data->flag_death)
	{
		i = 0;
		while (!philo->data->flag_death && i < philo->data->num_of_philo)
		{
			check_death(&philo[i]);
			i++;
		}
	}
}

int	init_data(t_data *data)
{
	int	i;

	i = 0;
	data->flag_death = 0;
	data->full_philo = 0;
	data->forks = malloc(sizeof(pthread_mutex_t *) * data->num_of_philo);
	if (!data->forks)
		return (1);
	while (i < data->num_of_philo)
	{
		data->forks[i] = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		if (!data->forks[i])
			return (1);
		pthread_mutex_init(data->forks[i], NULL);
		i++;
	}
	return (0);
}

int	init_philosophers(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		philo[i].id = i + 1;
		philo[i].data = data;
		if (philo[i].id % 2 == 0)
		{
			philo[i].left_fork = data->forks[i];
			philo[i].right_fork = data->forks[(i + 1) % data->num_of_philo];
		}
		else
		{
			philo[i].left_fork = data->forks[(i + 1) % data->num_of_philo];
			philo[i].right_fork = data->forks[i];
		}
		philo[i].times_of_eating = 0;
		i++;
	}
	return (0);
}

int	check_args(char *arg, t_data *data)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (ft_isdigit(arg[i]))
			i++;
		else
		{
			printf("Incorrect parameters - need only positive numbers.\n");
			free(data);
			exit(1);
		}
	}
	return (ft_atoi(arg));
}

int	parse_data(int argc, char **argv, t_data *data)
{
	if (argc < 5 || argc > 6)
	{
		printf("Incorrect numbers of parameters - need 4 or 5 parameters.\n");
		return (1);
	}
	data->num_of_philo = check_args(argv[1], data);
	data->time_to_die = check_args(argv[2], data);
	data->time_to_eat = check_args(argv[3], data);
	data->time_to_sleep = check_args(argv[4], data);
	if (argv[5])
		data->must_eat = check_args(argv[5], data);
	pthread_mutex_init(&data->print_message, NULL);
	pthread_mutex_init(&data->death, NULL);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data		*data;
	t_philo		*philo;
	pthread_t	*threads;
	int			i;

	data = malloc(sizeof(t_data));
	if (parse_data(argc, argv, data))
		return (1);
	philo = malloc(sizeof(t_philo) * data->num_of_philo);
	threads = malloc(sizeof(pthread_t) * data->num_of_philo);
	if (!philo || !threads)
		return (1);
	init_data(data);
	init_philosophers(data, philo);
	i = 0;
	while (i < data->num_of_philo)
	{
		philo[i].start_philo = get_time();
		pthread_create(&threads[i], NULL, life_cycle, &philo[i]);
		usleep(50);
		i++;
	}
	check_philo(philo);
	free_all(data, philo, threads);
	return (0);
}

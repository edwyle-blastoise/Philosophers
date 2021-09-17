/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblastoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 19:04:15 by eblastoi          #+#    #+#             */
/*   Updated: 2021/09/17 19:04:17 by eblastoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	usleep(10);
	while (i < data->num_of_philo)
	{
		if (data->full_philo == data->num_of_philo)
		{
			print_status(&philo[i], 7);
			return (1);
		}
		usleep(3);
		if (get_time() - philo[i].last_meal > (unsigned long)data->time_to_die)
		{
			print_status(&philo[i], 1);
			return (1);
		}
		i++;
		if (i == philo->data->num_of_philo)
			i = 0;
	}
	return (0);
}

t_philo	*init_philos(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		philo[i].id = i;
		philo[i].data = data;
		pthread_mutex_init(&philo[i].left_fork, NULL);
		pthread_mutex_init(&philo[i].philo_meal, NULL);
		philo[i].right_fork = &philo[i - 1].left_fork;
		philo[i].last_meal = get_time();
		philo[i].times_of_eating = 0;
		i++;
	}
	philo[0].right_fork = &philo[data->num_of_philo].left_fork;
	if (data->num_of_philo == 1)
		philo[0].right_fork = &philo[0].left_fork;
	return (philo);
}

int	check_args(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (ft_isdigit(arg[i]))
			i++;
		else
			return (0);
	}
	return (ft_atoi(arg));
}

int	parse_data(int argc, char **argv, t_data *data)
{
	if (argc < 5 || argc > 6)
		return (1);
	data->num_of_philo = check_args(argv[1]);
	data->time_to_die = check_args(argv[2]);
	data->time_to_eat = check_args(argv[3]);
	data->time_to_sleep = check_args(argv[4]);
	if (data->num_of_philo < 1 || data->time_to_die < 1 \
	|| data->time_to_eat < 1 || data->time_to_sleep < 1)
		return (1);
	if (argv[5])
	{
		data->must_eat = check_args(argv[5]);
		if (data->must_eat < 1)
			return (1);
	}
	pthread_mutex_init(&data->print_message, NULL);
	data->start_philo = get_time();
	data->full_philo = 0;
	return (0);
}

int	main(int argc, char **argv)
{
	int		i;
	t_data	data;
	t_philo	*philo;

	i = 0;
	if (parse_data(argc, argv, &data))
	{
		printf("Incorrect parameters!\n");
		return (1);
	}
	philo = malloc(sizeof(t_philo) * data.num_of_philo);
	if (!philo)
		return (1);
	init_philos(&data, philo);
	while (i < data.num_of_philo)
	{
		pthread_create(&philo[i].thread, NULL, life_cycle, &philo[i]);
		pthread_detach(philo[i].thread);
		i++;
	}
	check_death(&data, philo);
	free_all(&data, philo);
	return (0);
}

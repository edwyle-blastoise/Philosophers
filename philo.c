/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblastoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 17:01:38 by eblastoi          #+#    #+#             */
/*   Updated: 2021/09/16 17:01:39 by eblastoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	choose_message(t_philo *philo, int status)
{
	if (status == 1)
		printf("%llu %d died\n", get_time() - philo->start_philo, philo->id);
	else if (status == 2)
		printf("%llu %d take the left fork\n", \
		get_time() - philo->start_philo, philo->id);
	else if (status == 3)
		printf("%llu %d take the right fork\n", \
		get_time() - philo->start_philo, philo->id);
	else if (status == 4)
		printf("%llu %d is eating\n", \
		get_time() - philo->start_philo, philo->id);
	else if (status == 5)
		printf("%llu %d is sleeping\n", \
		get_time() - philo->start_philo, philo->id);
	else if (status == 6)
		printf("%llu %d is thinking\n", \
		get_time() - philo->start_philo, philo->id);
	else if (status == 7)
		printf("%llu %d put down the right fork\n", \
		get_time() - philo->start_philo, philo->id);
	else if (status == 8)
		printf("%llu %d put down the left fork\n", \
		get_time() - philo->start_philo, philo->id);
	else if (status == 9)
		printf("Each pholosopher ate %d times\n", philo->data->must_eat);
}

void	print_status(t_philo *philo, int status)
{
	pthread_mutex_lock(&philo->data->print_message);
	choose_message(philo, status);
	pthread_mutex_unlock(&philo->data->print_message);
}

void	philo_doings(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, 2);
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, 3);
	print_status(philo, 4);
	philo->last_meal = get_time();
	if (philo->times_of_eating++ == philo->data->must_eat)
	{
		philo->data->full_philo++;
		if (philo->data->full_philo == philo->data->num_of_philo)
		{
			philo->data->flag_death = 1;
			pthread_mutex_lock(&philo->data->death);
			print_status(philo, 9);
		}
	}
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	print_status(philo, 7);
	pthread_mutex_unlock(philo->left_fork);
	print_status(philo, 8);
	print_status(philo, 5);
	ft_usleep(philo->data->time_to_sleep);
	print_status(philo, 6);
}

void	*life_cycle(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	philo->last_meal = get_time();
	while (1)
		philo_doings(philo);
	return (NULL);
}

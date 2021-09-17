/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblastoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 19:04:27 by eblastoi          #+#    #+#             */
/*   Updated: 2021/09/17 19:04:29 by eblastoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	choose_message(t_philo *philo, int status)
{
	if (status == 1)
		printf("%lu %d died\n", \
		get_time() - philo->data->start_philo, philo->id);
	else if (status == 2)
		printf("%lu %d take the left fork\n", \
		get_time() - philo->data->start_philo, philo->id);
	else if (status == 3)
		printf("%lu %d take the right fork\n", \
		get_time() - philo->data->start_philo, philo->id);
	else if (status == 4)
		printf("%lu %d is eating\n", \
		get_time() - philo->data->start_philo, philo->id);
	else if (status == 5)
		printf("%lu %d is sleeping\n", \
		get_time() - philo->data->start_philo, philo->id);
	else if (status == 6)
		printf("%lu %d is thinking\n", \
		get_time() - philo->data->start_philo, philo->id);
	else if (status == 7)
		printf("Each philosopher ate %d times\n", philo->data->must_eat);
}

void	print_status(t_philo *philo, int status)
{
	pthread_mutex_lock(&philo->data->print_message);
	choose_message(philo, status);
	pthread_mutex_unlock(&philo->data->print_message);
}

void	philo_doings(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork);
	print_status(philo, 2);
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, 3);
	philo->last_meal = get_time();
	philo->times_of_eating++;
	if (philo->times_of_eating == philo->data->must_eat)
	{
		pthread_mutex_lock(&philo->philo_meal);
		philo->data->full_philo++;
		pthread_mutex_unlock(&philo->philo_meal);
	}
	print_status(philo, 4);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(&philo->left_fork);
	if (philo->times_of_eating == philo->data->must_eat)
		return ;
	print_status(philo, 5);
	ft_usleep((philo->data->time_to_sleep));
	print_status(philo, 6);
}

void	*life_cycle(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	if (philo->data->num_of_philo > 1)
		if (philo->id % 2 == 0)
			ft_usleep(philo->data->time_to_eat / 2);
	while (philo->times_of_eating != philo->data->must_eat)
		philo_doings(philo);
	return (NULL);
}

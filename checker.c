/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblastoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 17:06:24 by eblastoi          #+#    #+#             */
/*   Updated: 2021/09/16 17:06:26 by eblastoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

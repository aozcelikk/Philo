/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozcelik <42istanbul.com.tr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 12:12:44 by aozcelik          #+#    #+#             */
/*   Updated: 2022/08/31 12:12:45 by aozcelik         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_mutex(t_data *data)
{
	pthread_mutex_init(&data->meal, NULL);
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->m_checker, NULL);
}

void	destroy_mutex(t_data *data)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->meal);
	pthread_mutex_destroy(&data->m_checker);
	while (++i < data->number_of_philos)
		pthread_mutex_destroy(&data->forks[i]);
}

void	mutex_lock_fork(t_philo *philo)
{
	if (philo->philo_id == philo->struct_data->number_of_philos)
	{
		pthread_mutex_lock(&philo->struct_data->forks[philo->right_fork]);
		pthread_mutex_lock(&philo->struct_data->forks[philo->left_fork]);
	}
	else
	{
		pthread_mutex_lock(&philo->struct_data->forks[philo->left_fork]);
		pthread_mutex_lock(&philo->struct_data->forks[philo->right_fork]);
	}
}

void	mutex_unlock_fork(t_philo *philo)
{
	if (philo->philo_id == philo->struct_data->number_of_philos)
	{
		pthread_mutex_unlock(&philo->struct_data->forks[philo->right_fork]);
		pthread_mutex_unlock(&philo->struct_data->forks[philo->left_fork]);
	}
	else
	{
		pthread_mutex_unlock(&philo->struct_data->forks[philo->left_fork]);
		pthread_mutex_unlock(&philo->struct_data->forks[philo->right_fork]);
	}
}

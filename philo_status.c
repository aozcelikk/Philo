/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozcelik <42istanbul.com.tr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 12:12:54 by aozcelik          #+#    #+#             */
/*   Updated: 2022/08/31 12:12:55 by aozcelik         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(long int time_now, t_philo *philo, char *status)
{
	pthread_mutex_lock(&philo->struct_data->print);
	pthread_mutex_lock(&philo->struct_data->m_checker);
	if (philo->struct_data->checker != 1)
		printf("%ld %d %s\n", time_now
			- philo->struct_data->start_dinner, philo->philo_id, status);
	pthread_mutex_unlock(&philo->struct_data->m_checker);
	pthread_mutex_unlock(&philo->struct_data->print);
}

int	is_a_death_philo(t_data *data, int i)
{
	if (get_time() - data->philo[i].last_dinner > data->time_to_die)
	{
		print_status(get_time(), data->philo + i, "DIED");
		pthread_mutex_lock(&data->m_checker);
		data->checker = 1;
		pthread_mutex_unlock(&data->m_checker);
		pthread_mutex_unlock(&data->meal);
		return (1);
	}
	return (0);
}

int	all_philo_satisfied(t_data *data)
{
	if (data->ate_dinner == data->number_of_philos)
	{
		pthread_mutex_lock(&data->m_checker);
		data->checker = 1;
		pthread_mutex_unlock(&data->m_checker);
		return (1);
	}
	return (0);
}

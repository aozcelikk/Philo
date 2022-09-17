/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozcelik <42istanbul.com.tr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 12:13:16 by aozcelik          #+#    #+#             */
/*   Updated: 2022/08/31 12:13:17 by aozcelik         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_info(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philos)
	{
		data->philo[i].philo_id = i + 1;
		data->philo[i].left_fork = i;
		data->philo[i].right_fork = i + 1;
		data->philo[i].struct_data = data;
		data->philo[i].last_dinner = get_time();
		data->philo[i].had_dinner = 0;
		if (i + 1 == data->number_of_philos)
			data->philo[i].right_fork = 0;
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
}

void	start_struct(t_data *data, int argc, char **argv)
{																		
	data->number_of_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]) * 1000;
	data->time_to_sleep = ft_atoi(argv[4]) * 1000;
	if (argc > 5)
		data->to_dinner = ft_atoi(argv[5]);
	else
		data->to_dinner = 0;
	data->forks = NULL;
	data->philo = malloc(data->number_of_philos * sizeof(t_philo));
	data->forks = malloc(data->number_of_philos * sizeof(pthread_mutex_t));
	if (data->forks == NULL || data->philo == NULL)
	{
		printf("Could not malloc struct\n");
		return ;
	}
	data->ate_dinner = 0;
	ft_bzero(data->philo, sizeof(t_philo));
	return (philo_info(data));
}

int	create_philo(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->number_of_philos)
	{
		if (pthread_create(&data->philo[i].thread, NULL, &routine,
				&data->philo[i]) != 0)
			return (error(PTHREAD_FAILURE));
	}	
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	i = -1;
	init_mutex(&data);
	if (!error_check(argc, argv))
		return (1);
	data.start_dinner = get_time();
	start_struct(&data, argc, argv);
	create_philo(&data);
	if (pthread_create(&data.monitor, NULL, &died, &data) != 0)
		return (error(PTHREAD_FAILURE));
	if (pthread_join(data.monitor, NULL) != 0)
		return (error(JOIN_FAILURE));
	while (++i < data.number_of_philos)
	{
		if (pthread_join(data.philo[i].thread, NULL) != 0)
			return (error(JOIN_FAILURE));
	}
	usleep(1000);
	destroy_mutex(&data);
	free(data.philo);
	free(data.forks);
	return (0);
}

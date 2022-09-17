/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozcelik <42istanbul.com.tr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 12:13:32 by aozcelik          #+#    #+#             */
/*   Updated: 2022/08/31 12:13:34 by aozcelik         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdbool.h>
# include <limits.h>
# include <sys/time.h>

# define MIN_ARGS	5
# define MAX_ARGS	6

//error messages
# define USAGE "Usage: ./philo n_philo ms_to_die ms_to_eat ms_sleep [must_eat]"
# define NOT_UNINT "Arguments must be integers greater than 0"
# define PTHREAD_FAILURE "Could not create thread" 
# define JOIN_FAILURE "Could not join thread"

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				left_fork;
	int				right_fork;
	int				philo_id;
	int				had_dinner;
	long int		last_dinner;
	bool			eating;
	pthread_mutex_t	mutex;
	pthread_t		thread;
	t_data			*struct_data;
}				t_philo;

struct			s_data
{
	int				number_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				to_dinner;
	int				checker;
	int				ate_dinner;
	long int		start_dinner;
	t_philo			*philo;
	pthread_t		monitor;
	pthread_mutex_t	*forks;
	pthread_mutex_t	meal;
	pthread_mutex_t	m_checker;
	pthread_mutex_t	print;
};

//utils.c
bool		error(char *message);
int			ft_atoi(const char *ptr);
void		ft_bzero(void *s, size_t n);
double		philos_atoi(const char *ptr);
long int	get_time(void);

//utils_dinner.c
void		*died(void *param);
void		*one_philo(t_philo *philo);
void		eat(t_philo *philo);
void		*routine(void *param);

//error_check.c
bool		error_check(int argc, char **argv);
int			ft_isdigit(int c);

//mutex.c
void		init_mutex(t_data *data);
void		destroy_mutex(t_data *data);
void		mutex_lock_fork(t_philo *philo);
void		mutex_unlock_fork(t_philo *philo);

//philo_status.c
void		print_status(long int time_now, t_philo *philo, char *status);
int			is_a_death_philo(t_data *data, int i);
int			all_philo_satisfied(t_data *data);

#endif

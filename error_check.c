/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozcelik <42istanbul.com.tr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 12:13:23 by aozcelik          #+#    #+#             */
/*   Updated: 2022/08/31 12:13:24 by aozcelik         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_out_of_range(double number)
{
	if (number > INT_MAX || number == 0)
		return (true);
	return (false);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static bool	only_digits(char **argv, int i, int j)
{
	while (argv[i][++j])
		if (!ft_isdigit(argv[i][j]))
			return (false);
	return (true);
}

static bool	only_unsigned_integers(int argc, char **argv, int i)
{
	while (++i < argc)
	{
		if (!only_digits(argv, i, -1))
			return (false);
		if (is_out_of_range(philos_atoi(argv[i])))
			return (false);
	}
	return (true);
}

bool	error_check(int argc, char **argv)
{
	if (argc < MIN_ARGS || argc > MAX_ARGS)
		return (error(USAGE));
	if (!only_unsigned_integers(argc, argv, 0))
		return (error(NOT_UNINT));
	return (true);
}

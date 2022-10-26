/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/26 11:39:26 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/10/12 11:40:02 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	ft_atol(const char *str)
{
	int		index;
	long	num;

	index = 0;
	num = 0;
	while (str[index] >= '0' && str[index] <= '9')
	{
		num = num * 10 + (str[index] - 48);
		index++;
	}
	return (num);
}

int	check_input(char **arguments)
{
	int	i;
	int	j;

	i = 1;
	while (arguments[i])
	{
		j = 0;
		while (arguments[i][j])
		{
			if (arguments[i][j] < '0' || arguments[i][j] > '9')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	get_input(int argc, char **arguments, t_table *table)
{
	if (argc == 5 || argc == 6)
	{
		if (!check_input(arguments))
			return (0);
		table->n_philos = ft_atol(arguments[1]);
		table->t_to_die = ft_atol(arguments[2]);
		table->t_to_eat = ft_atol(arguments[3]);
		table->t_to_sleep = ft_atol(arguments[4]);
		if (arguments[5])
			table->n_meals = ft_atol(arguments[5]);
		else
			table->n_meals = 0;
		if (table->n_philos > INT_MAX || table->t_to_die > INT_MAX
			|| table->t_to_eat > INT_MAX || table->t_to_sleep > INT_MAX
			|| table->n_meals > INT_MAX || table->n_philos == 0)
			return (0);
	}
	else
		return (0);
	return (1);
}

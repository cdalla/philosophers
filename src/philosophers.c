/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 14:51:21 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/10/29 12:44:51 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	initial_info(t_table *t)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&t->start, NULL)
		|| pthread_mutex_init(&t->t_acc, NULL)
		|| pthread_mutex_init(&t->printf, NULL))
		return (0);
	while (i < t->n_philos)
	{
		if (pthread_mutex_init(&t->fork[i], NULL)
			|| pthread_mutex_init(&t->fork_av[i], NULL))
			return (0);
		t->philo[i].num = i + 1;
		t->philo[i].n_meals = 0;
		t->philo[i].last_meal = t->born_t;
		t->philo[i].t = t;
		i++;
	}
	return (1);
}

int	generate_threads(t_table *t)
{
	int	i;

	if (!initial_info(t))
		return (0);
	i = 0;
	t->th_created = 0;
	pthread_mutex_lock(&t->start);
	while (i < t->n_philos)
	{
		if (!pthread_create(&t->philo[i].thread, NULL, routine, &t->philo[i]))
			t->th_created += 1;
		i++;
	}
	pthread_mutex_unlock(&t->start);
	if (t->th_created < t->n_philos)
		return (0);
	return (1);
}

void	destroy_threads(t_table *t)
{
	int	i;

	i = 0;
	while (i < t->th_created)
	{
		pthread_join(t->philo[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < t->n_philos)
	{
		pthread_mutex_destroy(&t->fork[i]);
		pthread_mutex_destroy(&t->fork_av[i]);
		i++;
	}
	pthread_mutex_destroy(&t->start);
	pthread_mutex_destroy(&t->t_acc);
	pthread_mutex_destroy(&t->printf);
}

int	main(int argc, char **argv)
{
	t_table	t;

	t.born_t = get_time();
	t.state = 1;
	if (!get_input(argc, argv, &t))
	{
		printf("INPUT ERROR\n");
		return (0);
	}
	if (!generate_threads(&t))
		printf("THREAD ERROR\n");
	destroy_threads(&t);
	return (0);
}

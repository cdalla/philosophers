/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 14:51:21 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/10/26 13:19:17 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*

	USE A MUTEX TO CHECK FORK STATE INSTEAD OF STAY PENDING
	
	eat funct call sleep funct
	sleep funct recall sleep funct


	USE A MUTEX TO STOP THE PHILOS UNTIL ALL THE THREADS HAS BEEN CREATED

	CHECK THE NUMBER OF THREADS CREATED AND STOP THE PROGRAM IF SOME THREADS
	FAILED
	STOP THE ROUTINE FUNCTION BEFORE IT STARTS IF A THREAD CREATION FAILS
*/

#include "philosophers.h"

void	initial_info(t_table *t)
{
	int	i;

	i = 0;
	pthread_mutex_init(&t->start, NULL);
	pthread_mutex_init(&t->t_acc, NULL);
	pthread_mutex_init(&t->printf, NULL);
	while (i < t->n_philos)
	{
		pthread_mutex_init(&t->fork[i], NULL);
		pthread_mutex_init(&t->fork_av[i], NULL);
		t->philo[i].num = i + 1;
		t->philo[i].n_meals = 0;
		t->philo[i].last_meal = t->born_t;
		t->philo[i].t = t;
		i++;
	}
}

int	generate_threads(t_table *t)
{
	int	i;

	initial_info(t);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 14:51:21 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/10/26 11:13:17 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*

	USE A MUTEX TO CHECK FORK STATE INSTEAD OF STAY PENDING
	
	eat funct call sleep funct
	sleep funct recall sleep funct


	MUTEX FOR PRINTING

	!!!FIX ONE SINGLE PHILO!!!
*/

#include "philosophers.h"

void	start_routine(t_philo *philo)
{
	while (check_state(philo) && check_n_meals(philo))
	{
		if (grab_forks(philo, philo->num - 1))
		{
			while (check_state(philo) && check_n_meals(philo))
			{
				if (philo->num == 1)
				{
					if (grab_forks(philo, (philo->t->n_philos - 1)))
						eat_f(philo);
				}
				else
				{
					if (grab_forks(philo, (philo->num - 2)))
						eat_f(philo);
				}
				usleep(250);
			}
			pthread_mutex_unlock(&philo->t->fork[philo->num - 1]);
			return ;
		}
		usleep(250);
	}
	return ;
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if ((philo->num % 2) == 0)
		usleep(250);
	start_routine(philo);
	return (NULL);
}

int	generate_threads(t_table *t)
{
	int	i;

	i = 0;
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
	i = 0;
	while (i < t->n_philos)
	{
		if (pthread_create(&t->philo[i].thread, NULL, routine, &t->philo[i]))
			return (0);
		i++;
	}
	return (1);
}

void	destroy_threads(t_table *t)
{
	int	i;

	i = 0;
	if (t->n_philos == 1)
		pthread_mutex_unlock(&t->fork[0]);
	while (i < t->n_philos)
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
	{
		printf("THREAD ERROR\n");
		return (0);
	}
	destroy_threads(&t);
	return (0);
}

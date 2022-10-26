/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/26 13:17:28 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/10/26 13:22:22 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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
	pthread_mutex_lock(&philo->t->start);
	pthread_mutex_unlock(&philo->t->start);
	if (philo->t->th_created < philo->t->n_philos)
		return (NULL);
	if ((philo->num % 2) == 0)
		usleep(250);
	start_routine(philo);
	return (NULL);
}

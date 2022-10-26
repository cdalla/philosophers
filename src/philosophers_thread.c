/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers_thread.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 11:58:45 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/10/26 10:49:36 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_fork(t_philo *p, int n)
{
	pthread_mutex_lock(&p->t->fork_av[n]);
	p->t->av_forks[n] = 0;
	pthread_mutex_unlock(&p->t->fork[n]);
	pthread_mutex_unlock(&p->t->fork_av[n]);
}

int	grab_forks(t_philo *p, int n)
{
	pthread_mutex_lock(&p->t->fork_av[n]);
	if (p->t->av_forks[n] == 0)
	{
		p->t->av_forks[n] = 1;
		pthread_mutex_lock(&p->t->fork[n]);
		print_f("%u %d has taken a fork\n", p);
		pthread_mutex_unlock(&p->t->fork_av[n]);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&p->t->fork_av[n]);
		return (0);
	}
}

void	free_forks(t_philo *philo)
{
	free_fork(philo, philo->num - 1);
	if (philo->num == 1)
		free_fork(philo, (philo->t->n_philos - 1));
	else
		free_fork(philo, (philo->num - 2));
	if (check_n_meals(philo))
		sleep_f(philo);
}

void	eat_f(t_philo *philo)
{
	philo->last_meal = get_time();
	print_f("%u %d is eating\n", philo);
	if (f_usleep(philo->t->t_to_eat, philo))
	{
		philo->n_meals += 1;
		free_forks(philo);
	}
	else
	{
		free_fork(philo, philo->num - 1);
		if (philo->num == 1)
			free_fork(philo, (philo->t->n_philos - 1));
		else
			free_fork(philo, (philo->num - 2));
	}
	return ;
}

void	sleep_f(t_philo *philo)
{
	print_f("%u %d is sleeping\n", philo);
	if (!f_usleep(philo->t->t_to_sleep, philo))
		return ;
	print_f("%u %d is thinking\n", philo);
	start_routine(philo);
}

//philo grab the fork then wait until time to die
// void	start_solo_meal(t_philo *philo)
// {
// 	grab_forks(philo, philo->num - 1);
// 	f_usleep(philo->t->t_to_die, philo);
// 	print_f("%u &d died\n", philo);
// 	return ;
// }
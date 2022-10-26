/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 12:01:38 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/10/26 10:54:51 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

uint32_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	f_usleep(uint32_t ms, t_philo *philo)
{
	uint32_t	time;

	time = get_time();
	while ((get_time() - time) < ms)
	{
		usleep (250);
		if (!check_state(philo))
			return (0);
	}
	return (1);
}

void	print_f(char *s, t_philo *p)
{
	uint32_t	time;

	pthread_mutex_lock(&p->t->printf);
	if (check_state(p))
	{
		time = get_time() - p->t->born_t;
		printf(s, time, p->num);
	}
	pthread_mutex_unlock(&p->t->printf);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers_check.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 12:00:14 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/10/20 13:21:35 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//PHILO THREAD CHECKS TABLE_STATE AND HIS TIMER
int	check_state(t_philo *p)
{
	int			value;
	uint32_t	cur_time;

	cur_time = get_time();
	pthread_mutex_lock(&p->t->t_acc);
	value = p->t->state;
	pthread_mutex_unlock(&p->t->t_acc);
	if (!value)
		return (0);
	else if ((cur_time - p->last_meal) >= p->t->t_to_die)
	{
		pthread_mutex_lock(&p->t->t_acc);
		printf("%u %d died\n", get_time() - p->t->born_t, p->num);
		p->t->state = 0;
		pthread_mutex_unlock(&p->t->t_acc);
		return (0);
	}
	return (1);
}

//PHILO THREAD CHECKS HIS NUMBER OF MEALS
int	check_n_meals(t_philo *p)
{
	if (p->t->n_meals)
	{
		if (p->n_meals < p->t->n_meals)
			return (1);
		return (0);
	}
	return (1);
}

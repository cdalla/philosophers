/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdalla-s <cdalla-s@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 14:49:17 by cdalla-s      #+#    #+#                 */
/*   Updated: 2022/10/29 12:41:23 by cdalla-s      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdint.h>
# include <limits.h>

typedef struct s_philo
{
	pthread_t		thread;
	int				num;
	int				n_meals;
	uint32_t		last_meal;
	struct s_table	*t;
}				t_philo;

typedef struct s_table
{
	struct s_philo	philo[200];
	long			n_philos;
	long			n_meals;
	int				state;
	int				th_created;
	int				av_forks[200];
	uint32_t		t_to_die;
	uint32_t		t_to_eat;
	uint32_t		t_to_sleep;
	uint32_t		born_t;
	pthread_mutex_t	start;
	pthread_mutex_t	fork_av[200];
	pthread_mutex_t	fork[200];
	pthread_mutex_t	t_acc;
	pthread_mutex_t	printf;
}				t_table;

//INPUT
int			get_input(int argc, char **arguments, t_table *table);
int			check_input(char **arguments);
long		ft_atol(const char *str);

//UTILS
uint32_t	get_time(void);
int			f_usleep(uint32_t ms, t_philo *p);
void		print_f(char *s, t_philo *p);

//CHECK
int			check_n_meals(t_philo *p);
int			check_state(t_philo *p);

//ROUTINE
void		*routine(void *arg);
void		start_routine(t_philo *philo);

//PHILO ACTION
void		eat_f(t_philo *philo);
void		sleep_f(t_philo *philo);
int			grab_forks(t_philo *p, int n);
void		free_fork(t_philo *philo, int n);
void		free_forks(t_philo *philo);

//THREADS
int			generate_threads(t_table *t);
void		destroy_threads(t_table *t);
int			initial_info(t_table *t);

#endif
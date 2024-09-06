/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 19:17:43 by eviscont          #+#    #+#             */
/*   Updated: 2024/09/06 15:22:30 by eviscont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define PHILO_MAX 1000

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				meals;
	size_t			last_meal;
	size_t			start_time;
	pthread_mutex_t	*my_fork;
	pthread_mutex_t	*left_fork;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	int				nbr_philos;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				n_eat;
	int				dead_flag;
	int				start_flag;
	pthread_mutex_t	lock_dead;
	pthread_mutex_t	lock_start;
	pthread_mutex_t	lock_write;
	t_philo			*philo;
}					t_data;

//utils
int		ft_atoi(const char *str);
int		check_input(char **argv);
size_t	get_current_time(void);
void	ft_usleep(size_t milliseconds);
void	print_aux(char *str, t_philo *philo);

//philo
void	create_threads(t_philo *philo, int i);
void	*philo_routine(void *arg);
void	eating_routine(t_philo *philo);
void	set_dead(t_philo *philo);
int		check_dead(t_philo *philo);

//main
void	set_start(t_philo *philo);

#endif
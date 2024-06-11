/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:54:10 by usuario           #+#    #+#             */
/*   Updated: 2024/06/11 18:39:44 by eviscont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

int	check_dead(t_philo *philo)
{
	int	dead_flag;

	pthread_mutex_lock(&philo->data->lock_dead);
	dead_flag = philo->data->dead_flag;
	pthread_mutex_unlock(&philo->data->lock_dead);
	return (dead_flag);
}

void	set_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->lock_dead);
	philo->data->dead_flag = 1;
	pthread_mutex_unlock(&philo->data->lock_dead);
}

void	eating_routine(t_philo *philo)
{
	pthread_mutex_lock(philo->my_fork);
	print_aux("has taken a fork", philo);
	if (philo->left_fork == philo->my_fork)
	{
		pthread_mutex_unlock(philo->my_fork);
		print_aux("died", philo);
		set_dead(philo);
		return ;
	}
	pthread_mutex_lock(philo->left_fork);
	print_aux("has taken a fork", philo);
	philo->last_meal = get_current_time();
	print_aux("is eating", philo);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->my_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!philo->data->start_flag)
		ft_usleep(10);
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_to_eat / 2);
	while (!check_dead(philo))
	{
		eating_routine(philo);
		if (!philo->data->n_eat || (philo->meals < philo->data->n_eat))
			philo->meals++;
		else
			break ;
		print_aux("is sleeping", philo);
		ft_usleep(philo->data->time_to_sleep);
		print_aux("is thinking", philo);
	}
	return (arg);
}

void	create_threads(t_philo *p, int i)
{
	while (++i < p->data->nbr_philos)
	{
		if (pthread_create(&(p[i].thread), NULL, &philo_routine, &p[i]))
			printf("Failed to create thread");
	}
	set_start(p);
	while (!check_dead(p) && (!p->data->n_eat || (p->meals < p->data->n_eat)))
	{
		i = -1;
		while (++i < p->data->nbr_philos)
		{
			if ((get_current_time() - p[i].last_meal > p->data->time_to_die))
			{
				print_aux("died", &p[i]);
				set_dead(p);
			}
		}
	}
	i = -1;
	while (++i < p->data->nbr_philos)
	{
		if (pthread_join(p[i].thread, NULL) != 0)
			printf("Failed to join thread");
	}
}

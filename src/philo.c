/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usuario <usuario@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:54:10 by usuario           #+#    #+#             */
/*   Updated: 2024/06/10 02:46:50 by usuario          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

int	check_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->lock_dead);
	if (philo->data->dead_flag == 1)
	{
		pthread_mutex_unlock(&philo->data->lock_dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->lock_dead);
	return (0);
}

void	eating_routine(t_philo *philo)
{
	
	pthread_mutex_lock(philo->my_fork);
	print_aux("has taken a fork", philo);
	if (philo->data->nbr_philos == 1)
	{
		pthread_mutex_unlock(philo->my_fork);
		print_aux("is dead", philo);
		pthread_mutex_lock(&philo->data->lock_dead);
		philo->data->dead_flag = 1;
		pthread_mutex_unlock(&philo->data->lock_dead);
		return ;
	}
	pthread_mutex_lock(philo->left_fork);
	print_aux("has taken a fork", philo);
	print_aux("is eating", philo);
	philo->last_meal = get_current_time();
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->my_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_to_eat);
	while (1)
	{
		if ((get_current_time() - philo->last_meal > philo->data->time_to_die))
		{
			print_aux("is dead", philo);
			pthread_mutex_lock(&philo->data->lock_dead);
			philo->data->dead_flag = 1;
			pthread_mutex_unlock(&philo->data->lock_dead);
			break;
		}
		eating_routine(philo);
		if (philo->data->nbr_meals == 0 || (philo->meals < philo->data->nbr_meals))
			philo->meals++;
		else
			break;
		print_aux("is sleeping", philo);
		ft_usleep(philo->data->time_to_sleep);
		print_aux("is thinking", philo);
	}
	return (arg);
}

void	create_threads(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo[0].data->nbr_philos)
	{
		if (pthread_create(&philo[i].thread, NULL, &philo_routine, &philo[i]) != 0)
            printf("Failed to create thread");
		i++;
	}
	i = 0;
	while (i < philo[0].data->nbr_philos)
	{
		if (pthread_join(philo[i].thread, NULL) != 0)
			printf("Failed to join thread");
		i++;
	}
}

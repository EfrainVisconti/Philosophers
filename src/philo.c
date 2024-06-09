/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usuario <usuario@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:54:10 by usuario           #+#    #+#             */
/*   Updated: 2024/06/09 16:54:44 by usuario          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

void	eating_routine(t_philo *philo)
{
		pthread_mutex_lock(philo->my_fork);
		printf("%li %i has taken a fork\n", get_current_time(), philo->id);
		pthread_mutex_lock(philo->left_fork);
		printf("%li %i has taken a fork\n", get_current_time(), philo->id);
		printf("%li %i is eating\n", get_current_time(), philo->id);
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
	while (!philo->data->dead_flag)
	{
		if (philo->data->nbr_philos == 1 || (get_current_time() - philo->last_meal >= philo->data->time_to_die))
		{
			printf("%li %i is dead!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n", get_current_time(), philo->id);
			pthread_mutex_lock(&philo->data->lock_dead);
			philo->data->dead_flag = 1;
			pthread_mutex_unlock(&philo->data->lock_dead);
			break;
		}
		if (philo->data->nbr_meals == 0 || (philo->meals < philo->data->nbr_meals))
			philo->meals++;
		else
			break;
		eating_routine(philo);
		printf("%li %i is sleeping\n", get_current_time(), philo->id);
		ft_usleep(philo->data->time_to_sleep);
		printf("%li %i is thinking\n", get_current_time(), philo->id);
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

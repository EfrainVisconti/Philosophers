/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usuario <usuario@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 19:31:56 by eviscont          #+#    #+#             */
/*   Updated: 2024/06/08 23:26:23 by usuario          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->my_fork);
    printf("id: %i Enter to his fork\n", philo->id);
    pthread_mutex_unlock(philo->my_fork);
	pthread_mutex_lock(philo->left_fork);
    printf("id: %i Enter to his left fork\n", philo->id);
    pthread_mutex_unlock(philo->left_fork);
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

void	init_forks(pthread_mutex_t *forks, int n_philos)
{
	int	i;

	i = 0;
	while (i < n_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	init_philos(char *argv, t_philo *philo, t_data *data, pthread_mutex_t *forks)
{
	int				i;
	int				n_philos;

	n_philos = ft_atoi(argv);
	init_forks(forks, n_philos);
	i = 0;
	while (i < n_philos)
	{
		philo[i].id = i + 1;
		philo[i].meals = 0;
		philo[i].start_time = get_current_time();
		philo[i].last_meal = get_current_time();
		philo[i].data = data;
		philo[i].my_fork = &forks[i];
		if (i == n_philos - 1)
			philo[i].left_fork = &forks[0];
		else
			philo[i].left_fork = &forks[i + 1];
		i++;
	}
	data->philo = philo;
}

void	init_data(char	**argv, t_data *data)
{
	data->nbr_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5] != NULL)
		data->nbr_meals = ft_atoi(argv[5]);
	data->dead_flag = 0;
	pthread_mutex_init(&data->lock_dead, NULL);
}

int	main(int argc, char **argv)
{
	t_data			data;
	t_philo			philo[PHILO_MAX];
	pthread_mutex_t forks[PHILO_MAX];
	int				i;
	
	i = 0;
	if (argc < 5 || argc > 6 || ft_atoi(argv[1]) < 1 || ft_atoi(argv[2]) < 1
		|| ft_atoi(argv[3]) < 1 || ft_atoi(argv[4]) < 1)
		return (printf("Invalid arguments\n"), 1);
	if (check_input(argv) == 1)
		return (printf("Invalid character in input\n"), 2);
	if (ft_atoi(argv[1]) > PHILO_MAX)
		return (printf("Too many philosophers\n"), 3);
	init_data(argv, &data);
	init_philos(argv[1], philo, &data, forks);
	create_threads(philo);
	pthread_mutex_destroy(&(&data)->lock_dead);
	while (i < (&data)->nbr_philos)
		pthread_mutex_destroy(&forks[i++]);
	return (0);
}

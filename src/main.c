/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 19:31:56 by eviscont          #+#    #+#             */
/*   Updated: 2024/06/11 18:38:59 by eviscont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

void	set_start(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->lock_start);
	philo->data->start_flag = 1;
	pthread_mutex_unlock(&philo->data->lock_start);
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

void	init_philos(char *argv, t_philo *ph, t_data *data, pthread_mutex_t *fk)
{
	int				i;
	int				n_philos;

	n_philos = ft_atoi(argv);
	init_forks(fk, n_philos);
	i = 0;
	while (i < n_philos)
	{
		ph[i].id = i + 1;
		ph[i].meals = 0;
		ph[i].start_time = get_current_time();
		ph[i].last_meal = get_current_time();
		ph[i].data = data;
		ph[i].my_fork = &fk[i];
		if (i == n_philos - 1)
			ph[i].left_fork = &fk[0];
		else
			ph[i].left_fork = &fk[i + 1];
		i++;
	}
	data->philo = ph;
}

void	init_data(char	**argv, t_data *data)
{
	data->nbr_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5] != NULL)
		data->n_eat = ft_atoi(argv[5]);
	else
		data->n_eat = 0;
	data->dead_flag = 0;
	data->start_flag = 0;
	pthread_mutex_init(&data->lock_dead, NULL);
	pthread_mutex_init(&data->lock_write, NULL);
	pthread_mutex_init(&data->lock_start, NULL);
}

int	main(int argc, char **argv)
{
	t_data			data;
	t_philo			philo[PHILO_MAX];
	pthread_mutex_t	forks[PHILO_MAX];
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
	create_threads(philo, -1);
	pthread_mutex_destroy(&(&data)->lock_dead);
	pthread_mutex_destroy(&(&data)->lock_write);
	pthread_mutex_destroy(&(&data)->lock_start);
	while (i < (&data)->nbr_philos)
		pthread_mutex_destroy(&forks[i++]);
	return (0);
}

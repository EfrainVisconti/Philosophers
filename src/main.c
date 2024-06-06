/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 19:31:56 by eviscont          #+#    #+#             */
/*   Updated: 2024/06/06 20:50:18 by eviscont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

int	main(int argc, char **argv)
{
	if (argc < 5 || argc > 6 || ft_atoi(argv[1]) < 1 || ft_atoi(argv[2]) < 1
		|| ft_atoi(argv[3]) < 1 || ft_atoi(argv[4]) < 1)
		return (printf("Invalid arguments\n"), 1);
	if (check_input(argv) == 1)
		return (printf("Invalid character in input\n"), 2);
	if (ft_atoi(argv[1]) > 200)
		return (printf("Too many philosophers\n"), 3);
	return (0);
}

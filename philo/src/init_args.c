/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 19:58:06 by lgertrud          #+#    #+#             */
/*   Updated: 2025/09/02 16:13:04 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isspace(int c);

int	validate_args(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		printf(ERROR_NUM_ARGS);
		return (0);
	}
	if (!check_caracters(argv))
	{
		printf(ERROR_NO_ISDIGIT);
		return (0);
	}
	return (1);
}

int	check_caracters(char **arr)
{
	int	i;
	int	k;

	i = 1;
	while (arr[i])
	{
		k = 0;
		while (arr[i][k])
		{
			if ((!ft_isdigit(arr[i][k]) && !ft_isspace(arr[i][k]))
					|| !ft_atoi(arr[i]))
				return (0);
			k++;
		}
		i++;
	}
	return (1);
}

void	set_args(t_rules *rules, char **argv)
{
	int	i;

	rules->num_philos = ft_atoi(argv[1]);
	rules->time_to_die = ft_atoi(argv[2]) * 1000;
	rules->time_to_eat = ft_atoi(argv[3]) * 1000;
	rules->time_to_sleep = ft_atoi(argv[4]) * 1000;
	rules->meals_limit = 0;
	if (argv[5])
		rules->meals_limit = ft_atoi(argv[5]);
	rules->someone_died = 0;
	rules->forks = malloc(sizeof(pthread_mutex_t) * rules->num_philos);
	i = 0;
	while (i < rules->num_philos)
	{
		pthread_mutex_init(&rules->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&rules->print_lock, NULL);
}

t_philosopher	*ft_init_philos(t_rules *rules)
{
	t_philosopher	*philos;
	int				i;

	philos = malloc(sizeof(t_philosopher) * rules->num_philos);
	if (!philos)
		return (NULL);
	i = 0;
	rules->start = timestamp_ms();
	while (i < rules->num_philos)
	{
		philos[i].id = i + 1;
		philos[i].rules = rules;
		philos[i].last_meal = rules->start;
		philos[i].count_eat = 0;
		i++;
	}
	return (philos);
}

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

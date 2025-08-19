/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 19:58:06 by lgertrud          #+#    #+#             */
/*   Updated: 2025/08/19 14:45:15 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int ft_isspace(int c);

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
			if ((!ft_isdigit(arr[i][k]) && !ft_isspace(arr[i][k])) || !ft_atoi(arr[i]))
				return (0);
			k++;
		}
		i++;
	}
	return (1);
}

void	set_args(t_args *args, char **argv)
{
	args->philos = ft_atoi(argv[1]);
	args->die = ft_atoi(argv[2]);
	args->eat = ft_atoi(argv[3]);
	args->sleep = ft_atoi(argv[4]);
	if(argv[5])
		args->limit = ft_atoi(argv[5]);
}

int ft_isspace(int c)
{
    if (c == ' ' || c == '\t' || c == '\n' ||
        c == '\v' || c == '\f' || c == '\r')
        return 1;
    return 0;
}


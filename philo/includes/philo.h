/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 19:44:24 by lgertrud          #+#    #+#             */
/*   Updated: 2025/08/19 14:46:23 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define ERROR_NUM_ARGS "Usage: number_of_philosophers time_to_die time_to_eat time_to_sleep \
[number_of_times_each_philosopher_must_eat]\n"
# define ERROR_NO_ISDIGIT "Error: Invalid input. Each parameter \
must be a single positive numeric value.\n"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_args
{
	int	philos;
	int	die;
	int	eat;
	int	sleep;
	int	limit;
}	t_args;

// Init args
int		validate_args(int argc, char **argv);
int		check_caracters(char **arr);
void	set_args(t_args *args, char **argv);
// support functions
int		ft_atoi(const char *nptr);
char	*ft_strtrim(char const *s, char const *set);
int		ft_isdigit(int c);
size_t	ft_strlen(const char *str);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 19:43:07 by lgertrud          #+#    #+#             */
/*   Updated: 2025/08/19 14:42:35 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_args *args;

	if (!validate_args(argc, argv))
		return (1);
	args = malloc(sizeof(t_args));
	set_args(args, argv);
	free(args);
}

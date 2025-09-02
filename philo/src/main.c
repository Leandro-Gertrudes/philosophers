/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 19:43:07 by lgertrud          #+#    #+#             */
/*   Updated: 2025/09/02 16:15:49 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_rules			*rules;
	t_philosopher	*philos;

	if (!validate_args(argc, argv))
		return (1);
	rules = malloc(sizeof(t_rules));
	set_args(rules, argv);
	philos = ft_init_philos(rules);
	if (philos)
	{
		ft_philosophers(philos, rules);
		free(philos);
	}
	free(rules->forks);
	free(rules);
}

void	log_action(t_philosopher *philo, const char *action, t_rules *rules)
{
	pthread_mutex_lock(&philo->rules->print_lock);
	if (!philo->rules->someone_died)
		printf("[%ld] %d %s\n",
			timestamp_ms() - rules->start, philo->id, action);
	pthread_mutex_unlock(&philo->rules->print_lock);
}

long	timestamp_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000L);
}

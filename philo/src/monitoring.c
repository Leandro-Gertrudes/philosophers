/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:50:13 by lgertrud          #+#    #+#             */
/*   Updated: 2025/09/04 13:08:27 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_routine(void *arg)
{
	t_philosopher	*philos;
	t_rules			*rules;
	int				i;
	long			now;

	philos = (t_philosopher *)arg;
	rules = philos[0].rules;
	while (!rules->someone_died)
	{
		i = -1;
		while (++i < rules->num_philos)
		{
			now = timestamp_ms();
			if (now - philos[i].last_meal >= rules->time_to_die
				&& !(rules->meals_limit
					&& philos[i].count_eat >= rules->meals_limit))
			{
				return (someone_dead(philos, rules, i, now));
			}
			if (is_finished(philos, rules, i))
				return (NULL);
		}
		//usleep(100);
	}
	return (NULL);
}

void	*someone_dead(t_philosopher *philos, t_rules *rules, int i, long now)
{
	pthread_mutex_lock(&rules->print_lock);
	if (!rules->someone_died)
		printf("%ld %d died\n", now - rules->start, philos[i].id);
	rules->someone_died = 1;
	pthread_mutex_unlock(&rules->print_lock);
	return (NULL);
}

int	is_finished(t_philosopher *philos, t_rules *rules, int i)
{
	int	finished;

	finished = 1;
	if (!(rules->meals_limit && philos[i].count_eat >= rules->meals_limit))
		finished = 0;
	if (finished)
	{
		rules->someone_died = 1;
	}
	return (finished);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 12:00:52 by lgertrud          #+#    #+#             */
/*   Updated: 2025/09/04 16:13:04 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*unlock_and_return(t_rules *rules, t_philosopher *philo);

void	ft_philosophers(t_philosopher *philos, t_rules *rules)
{
	pthread_t	*threads;
	pthread_t	monitoring;
	int			i;
	int			j;

	threads = malloc(sizeof(pthread_t) * rules->num_philos);
	i = 0;
	while (i < rules->num_philos)
	{
		pthread_create(&threads[i], NULL, philosopher_routine, &philos[i]);
		i++;
	}
	pthread_create(&monitoring, NULL, monitor_routine, philos);
	j = -1;
	while (++j < rules->num_philos)
		pthread_join(threads[j], NULL);
	pthread_join(monitoring, NULL);
	j = -1;
	while (++j < rules->num_philos)
		pthread_mutex_destroy(&rules->forks[j]);
	pthread_mutex_destroy(&rules->print_lock);
	free(threads);
}

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philo;
	t_rules			*rules;

	philo = (t_philosopher *)arg;
	rules = philo->rules;
	if (rules->num_philos == 1)
		return (ft_one_philo(philo, rules));
	while (!rules->someone_died
		&& !(rules->meals_limit && philo->count_eat == rules->meals_limit))
	{
		ft_take_forks(philo, rules);
		philo->last_meal = timestamp_ms();
		log_action(philo, "is eating", rules);
		philo->count_eat++;
		if(!advance_time(rules, rules->time_to_eat))
			return (unlock_and_return(rules, philo));
		log_action(philo, "is sleeping", rules);
		pthread_mutex_unlock(&rules->forks[philo->id % rules->num_philos]);
		pthread_mutex_unlock(&rules->forks[philo->id - 1]);
		if(!advance_time(rules, rules->time_to_eat))
			return (NULL);
		log_action(philo, "is thinking", rules);
	}
	return (NULL);
}

void	ft_take_forks(t_philosopher *philo, t_rules *rules)
{
	int	left;
	int	right;

	left = philo->id - 1;
	right = (philo->id % rules->num_philos);
	if (philo->id % 2 == 0)
		{
			if (pthread_mutex_trylock(&rules->forks[right]) == 0)
			{
				log_action(philo, "has taken a fork", rules);
				if (pthread_mutex_trylock(&rules->forks[left]) == 0)
				{
					log_action(philo, "has taken a fork", rules);
					return ; // Pegou ambos os garfos, pode comer
				}
				else
					pthread_mutex_unlock(&rules->forks[right]); // libera direito se não conseguiu esquerdo
			}
		}
		else
		{
			if (pthread_mutex_trylock(&rules->forks[left]) == 0)
			{
				log_action(philo, "has taken a fork", rules);
				if (pthread_mutex_trylock(&rules->forks[right]) == 0)
				{
					log_action(philo, "has taken a fork", rules);
					return ; // Pegou ambos os garfos, pode comer
				}
				else
					pthread_mutex_unlock(&rules->forks[left]); // libera esquerdo se não conseguiu direito
			}
	}
}

void	*ft_one_philo(t_philosopher *philo, t_rules *rules)
{
	pthread_mutex_lock(&rules->forks[0]);
	log_action(philo, "has taken a fork", rules);
	usleep(rules->time_to_die);
	log_action(philo, "died", rules);
	rules->someone_died = 1;
	pthread_mutex_unlock(&rules->forks[0]);
	return (NULL);
}

void	*unlock_and_return(t_rules *rules, t_philosopher *philo)
{
	pthread_mutex_unlock(&rules->forks[philo->id - 1]);
	pthread_mutex_unlock(&rules->forks[philo->id % rules->num_philos]);
	return (NULL);
}

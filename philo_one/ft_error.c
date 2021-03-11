#include "philo_one.h"

static void		ft_putstr_fd(char *s, int fd)
{
	size_t	len;

	if (s == NULL)
		return ;
	len = 0;
	while (s && s[len])
		len++;
	write(fd, s, len);
}

int				ft_printerror(int errnum, pthread_mutex_t *write_lock)
{
	if (write_lock && pthread_mutex_lock(write_lock))
		return (ft_printerror(MUTEXF, NULL));
	if (errnum == BADARG)
		ft_putstr_fd("Error: bad arguments\n", 2);
	else if (errnum == MALLOC)
		ft_putstr_fd("Error: malloc failed\n", 2);
	else if (errnum == NEFORK)
		ft_putstr_fd("Error: less than two forks available\n", 2);
	else if (errnum == THREAD)
		ft_putstr_fd("Error: pthread failed\n", 2);
	else if (errnum == MUTEXF)
		ft_putstr_fd("Error: mutex failed\n", 2);
	if (write_lock && pthread_mutex_unlock(write_lock))
		return (ft_printerror(MUTEXF, NULL));
	return (1);
}

static void		ft_cleanthreads(t_common *ph)
{
	int		i;

	i = -1;
	while (++i < ph->conf->number)
	{
		if (ph->philo)
		{
			if (pthread_mutex_destroy(ph->philo[i].lastmeal_lock))
				ft_printerror(MUTEXF, NULL);
			free(ph->philo[i].lastmeal_lock);
		}
		if (ph->forks)
		{
			if (pthread_mutex_destroy(ph->forks[i].fork))
				ft_printerror(MUTEXF, NULL);
			free(ph->forks[i].fork);
		}
		if (ph->threads)
			free(ph->threads[i]);
	}
}

void			ft_cleanup(t_common *ph)
{
	ft_cleanthreads(ph);
	if (ph->conf->state_lock)
		if (pthread_mutex_destroy(ph->conf->state_lock))
			ft_printerror(MUTEXF, NULL);
	free(ph->conf->state_lock);
	if (ph->conf->write_lock)
		if (pthread_mutex_destroy(ph->conf->write_lock))
			ft_printerror(MUTEXF, NULL);
	free(ph->conf->write_lock);
	free(ph->threads);
	free(ph->forks);
	free(ph->philo);
}

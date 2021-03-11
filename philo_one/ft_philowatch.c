#include "philo_one.h"

int				ft_checkstate(t_philo *ph)
{
	int		res;

	res = 0;
	if (pthread_mutex_lock(ph->conf->state_lock))
		return (ft_printerror(MUTEXF, ph->conf->write_lock));
	if (ph->conf->state == DIED)
		res = 1;
	if (pthread_mutex_unlock(ph->conf->state_lock))
		return (ft_printerror(MUTEXF, ph->conf->write_lock));
	return (res);
}

static int		ft_setstatedead(t_common *ph, int i)
{
	if (pthread_mutex_lock(ph->conf->state_lock))
		return (ft_printerror(MUTEXF, ph->conf->write_lock));
	if (ph->philo[i].eaten_times != ph->conf->eating_times)
		ph->conf->state = DIED;
	if (ph->conf->state == DIED)
		ft_printstate(&(ph->philo[i]), DIED);
	if (pthread_mutex_unlock(ph->conf->state_lock))
		return (ft_printerror(MUTEXF, ph->conf->write_lock));
	return (0);
}

int				ft_philowatch(t_common *ph)
{
	int		i;

	i = 0;
	while (1)
	{
		usleep(100);
		if (pthread_mutex_lock(ph->philo[i].lastmeal_lock))
			return (ft_printerror(MUTEXF, ph->conf->write_lock));
		if (ft_getms() - ph->philo[i].lastmeal_ms > ph->conf->ms_to_die)
		{
			if (ft_setstatedead(ph, i))
				return (1);
			if (pthread_mutex_unlock(ph->philo[i].lastmeal_lock))
				return (ft_printerror(MUTEXF, ph->conf->write_lock));
			break ;
		}
		if (pthread_mutex_unlock(ph->philo[i].lastmeal_lock))
			return (ft_printerror(MUTEXF, ph->conf->write_lock));
		++i;
		if (i >= ph->conf->number)
			i = 0;
	}
	return (0);
}

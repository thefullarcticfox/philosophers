#include "philo_two.h"

int			ft_philocomplete(t_philo *ph)
{
	if (sem_wait(ph->conf->state_lock) < 0)
		ft_printerror(SEMAPH, ph->conf->write_lock);
	ph->conf->state = COMPLETE;
	if (sem_post(ph->conf->state_lock) < 0)
		ft_printerror(SEMAPH, ph->conf->write_lock);
	if (sem_wait(ph->conf->statuses_lock) < 0)
		ft_printerror(SEMAPH, ph->conf->write_lock);
	ph->conf->statuses[ph->n - 1] = COMPLETE;
	if (sem_post(ph->conf->statuses_lock) < 0)
		ft_printerror(SEMAPH, ph->conf->write_lock);
	return (0);
}

int			ft_checkstate(t_philo *ph)
{
	if (sem_wait(ph->conf->state_lock) < 0)
		return (ft_printerror(SEMAPH, ph->conf->write_lock));
	if (ph->conf->state == DIED)
	{
		if (sem_post(ph->conf->state_lock) < 0)
			return (ft_printerror(SEMAPH, ph->conf->write_lock));
		return (1);
	}
	if (ft_getms() - ph->lastmeal_ms > ph->conf->ms_to_die)
	{
		if (ph->eaten_times != ph->conf->eating_times)
			ph->conf->state = DIED;
		if (ph->conf->state == DIED)
			ft_printstate(ph, DIED);
		if (sem_post(ph->conf->state_lock) < 0)
			return (ft_printerror(SEMAPH, ph->conf->write_lock));
		return (1);
	}
	if (sem_post(ph->conf->state_lock) < 0)
		return (ft_printerror(SEMAPH, ph->conf->write_lock));
	return (0);
}

int			ft_confirmcomplete(t_common *ph)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (sem_wait(ph->conf->statuses_lock) < 0)
		return (ft_printerror(SEMAPH, ph->conf->write_lock));
	while (++i < ph->conf->number)
		if (ph->conf->statuses[i] == COMPLETE)
			j++;
	if (sem_post(ph->conf->statuses_lock) < 0)
		return (ft_printerror(SEMAPH, ph->conf->write_lock));
	if (j == ph->conf->number)
		return (1);
	return (0);
}

int			ft_philowatch(t_common *ph)
{
	while (1)
	{
		usleep(100);
		if (sem_wait(ph->conf->state_lock) < 0)
			return (ft_printerror(SEMAPH, ph->conf->write_lock));
		if (ph->conf->state == DIED)
		{
			if (sem_post(ph->conf->state_lock) < 0)
				return (ft_printerror(SEMAPH, ph->conf->write_lock));
			break ;
		}
		if (ph->conf->state == COMPLETE)
		{
			if (sem_post(ph->conf->state_lock) < 0)
				return (ft_printerror(SEMAPH, ph->conf->write_lock));
			if (ft_confirmcomplete(ph))
				break ;
		}
		if (sem_post(ph->conf->state_lock) < 0)
			return (ft_printerror(SEMAPH, ph->conf->write_lock));
	}
	return (0);
}
